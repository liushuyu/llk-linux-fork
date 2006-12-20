/***************************************************************************
 *            llk_inifile.h
 *
 *  Fri Sep 23 08:53:58 2005
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
 

#ifndef __LLK_INIFILE
#define __LLK_INIFILE

#include <glib.h>
#include <glib/gi18n.h>

typedef struct
{
  gchar *key;
  gchar *value;
}IniLine;    /* define the line in the ini file */

typedef struct
{
  gchar *name;  /* section name */
  GList *lines; /* list of all the lines in a section */
}IniSection; /* define the section in the ini file */

typedef struct
{
  gchar *filename;
  GList *sections; /* list of all the sections */
  gboolean changed; /* Whether changed */
}IniFile;    /* define ini file */

IniFile* ini_file_new(void);    /* creat ini file instance */
IniFile* ini_file_open_file(gchar *filename);
gboolean ini_file_write_file(IniFile* ini, gchar* filename);

void ini_file_free(IniFile* ini);
/* read key value in ini file */
gboolean ini_file_read_string  (IniFile* ini, gchar* section, gchar* key, gchar** value   );
gboolean ini_file_read_int     (IniFile* ini, gchar* section, gchar* key, gint* value     );
gboolean ini_file_read_boolean (IniFile* ini, gchar* section, gchar* key, gboolean* value );
/* save key value in ini file */
void ini_file_write_string (IniFile* ini, gchar* section, gchar* key, gchar* value    );
void ini_file_write_int    (IniFile* ini, gchar* section, gchar* key, gint value      );
void ini_file_write_boolean(IniFile* ini, gchar* section, gchar* key, gboolean value  );
/* rename and remove key and section */
gboolean ini_file_rename_section(IniFile* ini, gchar* section, gchar* section_name);
gboolean ini_file_remove_key    (IniFile* ini, gchar* section, gchar* key         );
gboolean ini_file_remove_section(IniFile* ini, gchar* section                     );

#endif
