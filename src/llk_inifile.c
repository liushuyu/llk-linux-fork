/***************************************************************************
 *            llk_inifile.c
 *
 *  Fri Sep 23 08:53:04 2005
 *  Copyright  2005  Alpher
 *  Email: alpher_zmx@yahoo.com.cn
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <llk_inifile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static IniSection *ini_file_create_section(IniFile *ini, gchar *name);
static IniLine *ini_file_create_string(IniSection *section, gchar *key,
                                       gchar *value);
static IniSection *ini_file_find_section(IniFile *ini, gchar *name);
static IniLine *ini_file_find_string(IniSection *section, gchar *key);

static IniSection *ini_file_create_section(IniFile *ini, gchar *name) {
  IniSection *section;
  section = (IniSection *)g_malloc0(sizeof(IniSection));
  section->name = g_strdup(name);
  ini->sections = g_list_append(ini->sections, section);
  return section;
}

static IniLine *ini_file_create_string(IniSection *section, gchar *key,
                                       gchar *value) {
  IniLine *line;
  line = (IniLine *)g_malloc0(sizeof(IniLine));
  line->key = g_strchug(g_strchomp(g_strdup(key)));
  line->value = g_strchug(g_strchomp(g_strdup(value)));
  section->lines = g_list_append(section->lines, line);
  return line;
}

static IniSection *ini_file_find_section(IniFile *ini, gchar *name) {
  IniSection *section;
  GList *list;
  list = ini->sections;
  while (list) {
    section = (IniSection *)list->data;
    if (!strcasecmp(section->name, name))
      return section;
    list = g_list_next(list);
  }
  return NULL;
}

static IniLine *ini_file_find_string(IniSection *section, gchar *key) {
  IniLine *line;
  GList *list;
  list = section->lines;
  while (list) {
    line = (IniLine *)list->data;
    if (!strcasecmp(line->key, key))
      return line;
    list = g_list_next(list);
  }
  return NULL;
}

IniFile *ini_file_new(void) {
  IniFile *ini;
  ini = (IniFile *)g_malloc0(sizeof(IniFile));
  return ini;
}

IniFile *ini_file_open_file(gchar *filename) {
  IniFile *ini;
  FILE *file;
  gchar *buffer, **lines, *tmp;
  gint i;
  struct stat stats;
  IniSection *section = NULL;
  if (lstat(filename, &stats) == -1)
    return NULL;
  if (!(file = fopen(filename, "r")))
    return NULL;
  buffer = (gchar *)g_malloc(stats.st_size + 1);
  if (fread(buffer, 1, stats.st_size, file) != stats.st_size) {
    g_free(buffer);
    fclose(file);
    return NULL;
  }
  fclose(file);
  buffer[stats.st_size] = '\0';
  ini = (IniFile *)g_malloc0(sizeof(IniFile));
  ini->filename = g_strdup(filename);
  ini->changed = FALSE;
  lines = g_strsplit(buffer, "\n", 0);
  g_free(buffer);
  i = 0;
  while (lines[i]) {
    if (lines[i][0] == '[') {
      if ((tmp = strchr(lines[i], ']'))) {
        *tmp = '\0';
        section = ini_file_create_section(ini, &lines[i][1]);
      }
    } else if (lines[i][0] != '#' && section) {
      if ((tmp = strchr(lines[i], '='))) {
        *tmp = '\0';
        tmp++;
        ini_file_create_string(section, lines[i], tmp);
      }
    }
    i++;
  }
  g_strfreev(lines);
  return ini;
}

gboolean ini_file_write_file(IniFile *ini, gchar *filename) {
  FILE *file;
  GList *section_list, *line_list;
  IniSection *section;
  IniLine *line;
  if (!(file = fopen(filename, "w")))
    return FALSE;
  /* Write warring message */
  fprintf(file, _("# DO NOT Modify this file by hand unless you exactly know "
                  "what you are doing.\n"));
  section_list = ini->sections;
  while (section_list) {
    section = (IniSection *)section_list->data;
    fprintf(file, "[%s]\n", section->name);
    if (section->lines) {
      line_list = section->lines;
      while (line_list) {
        line = (IniLine *)line_list->data;
        fprintf(file, "%s=%s\n", line->key, line->value);
        line_list = g_list_next(line_list);
      }
    }
    section_list = g_list_next(section_list);
  }
  fclose(file);
  return TRUE;
}

void ini_file_free(IniFile *ini) {
  IniSection *section;
  IniLine *line;
  GList *section_list, *line_list;
  g_free(ini->filename);
  section_list = ini->sections;
  while (section_list) {
    section = (IniSection *)section_list->data;
    g_free(section->name);
    line_list = section->lines;
    while (line_list) {
      line = (IniLine *)line_list->data;
      g_free(line->key);
      g_free(line->value);
      g_free(line);
      line_list = g_list_next(line_list);
    }
    g_list_free(section->lines);
    g_free(section);
    section_list = g_list_next(line_list);
  }
  g_list_free(ini->sections);
  ini->sections = NULL;
  ini->filename = NULL;
}

gboolean ini_file_read_string(IniFile *ini, gchar *section, gchar *key,
                              gchar **value) {
  IniSection *sect;
  IniLine *line;
  *value = NULL;
  if (!(sect = ini_file_find_section(ini, section)))
    return FALSE;
  if (!(line = ini_file_find_string(sect, key)))
    return FALSE;
  *value = g_strdup(line->value);
  return TRUE;
}

gboolean ini_file_read_int(IniFile *ini, gchar *section, gchar *key,
                           gint *value) {
  gchar *str;
  if (!ini_file_read_string(ini, section, key, &str)) {
    *value = 0;
    return FALSE;
  }
  *value = atoi(str);
  g_free(str);
  return TRUE;
}

gboolean ini_file_read_boolean(IniFile *ini, gchar *section, gchar *key,
                               gboolean *value) {
  gchar *str;
  if (!ini_file_read_string(ini, section, key, &str)) {
    *value = FALSE;
    return FALSE;
  }
  if (!strcmp(str, "0"))
    *value = FALSE;
  else
    *value = TRUE;
  g_free(str);
  return TRUE;
}

void ini_file_write_string(IniFile *ini, gchar *section, gchar *key,
                           gchar *value) {
  IniSection *sect;
  IniLine *line;
  ini->changed = TRUE;
  sect = ini_file_find_section(ini, section);
  if (!sect)
    sect = ini_file_create_section(ini, section);
  if ((line = ini_file_find_string(sect, key))) {

    g_free(line->value);
    line->value = g_strchug(g_strchomp(g_strdup(value)));
  } else
    ini_file_create_string(sect, key, value);
}

void ini_file_write_int(IniFile *ini, gchar *section, gchar *key, gint value) {
  gchar *strvalue;
  strvalue = g_strdup_printf("%d", value);
  ini_file_write_string(ini, section, key, strvalue);
  g_free(strvalue);
}

void ini_file_write_boolean(IniFile *ini, gchar *section, gchar *key,
                            gboolean value) {
  if (value)
    ini_file_write_string(ini, section, key, "1");
  else
    ini_file_write_string(ini, section, key, "0");
}

gboolean ini_file_rename_section(IniFile *ini, gchar *section,
                                 gchar *section_name) {
  IniSection *sect;
  sect = ini_file_find_section(ini, section);
  if (sect) {
    ini->changed = TRUE;
    g_free(sect->name);
    sect->name = g_strdup(section_name);
  }
  return TRUE;
}

gboolean ini_file_remove_key(IniFile *ini, gchar *section, gchar *key) {
  IniSection *sect;
  IniLine *line;
  sect = ini_file_find_section(ini, section);
  if (sect) {
    line = ini_file_find_string(sect, key);
    if (line) {
      ini->changed = TRUE;
      sect->lines = g_list_remove(sect->lines, line);
      g_free(line->key);
      g_free(line->value);
      g_free(line);
    }
  }
  return TRUE;
}

gboolean ini_file_remove_section(IniFile *ini, gchar *section) {
  IniSection *sect;
  IniLine *line;
  GList *line_list;
  sect = ini_file_find_section(ini, section);
  if (sect) {
    ini->changed = TRUE;
    g_free(sect->name);
    line_list = sect->lines;
    while (line_list) {
      line = (IniLine *)line_list->data;
      g_free(line->key);
      g_free(line->value);
      g_free(line);
      line_list = g_list_next(line_list);
    }
    ini->sections = g_list_remove(ini->sections, sect);
    g_list_free(sect->lines);
    g_free(sect);
  }
  return TRUE;
}
