/***************************************************************************
 *            llk_about.c
 *
 *  Fri Sep 23 08:56:08 2005
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

#include <config.h>
#include <llk_about.h>
void show_about(void) {
  GtkWidget *dialog, *button, *label;
  gchar *title = NULL;
  dialog = gtk_dialog_new();
  title = g_strdup_printf("%s%s", _("About llk_linux Version"), VERSION);
  gtk_window_set_title(GTK_WINDOW(dialog), title);
  g_free(title);
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);
  label = gtk_label_new(_("llk_linux Designed by Alpher\n\
by Zhao Mingxian <alpher_zmx@yahoo.com.cn>\n\
Copyright (C) 2005 Zhao Mingxian\n\
\n\
This program is free software; you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation; either version 2 of the License, or  \n\
(at your option) any later version.                               \n\
\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the \n\
GNU General Public License for more details.                  \n\
\n\
This Software is designed in C,with GTK+ 2.0 library.\n\
It's project websit is at:llk-linux.sourceforge.net\n\
and forum in China is at:www.linuxfans.org.\n\
\n\
You should have received a copy of the GNU General Public License\n\
along with this program; if not, write to the Free Software\n\
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307  USA"));

  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), label, TRUE, TRUE, 0);
  gtk_widget_show(label);

  button = gtk_dialog_add_button(GTK_DIALOG(dialog), _("Close"),
                                 GTK_RESPONSE_ACCEPT);
  gtk_widget_show(button);
  gtk_widget_grab_focus(button);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

void show_rule(void) {
  GtkWidget *dialog, *button, *image, *label;
  static GdkPixbuf *rule_pixbuf = NULL;

  dialog = gtk_dialog_new();
  gtk_window_set_title(GTK_WINDOW(dialog), _("llk_linux game rules"));
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);
  if (rule_pixbuf == NULL) {
    if (!ExtractSingleFile("HowToPlay.jpg")) {
      label = gtk_label_new(_("Extract HowToPlay.jpg failed."));
      gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), label, TRUE, TRUE,
                         0);
      gtk_widget_show(label);
    } else {
      rule_pixbuf = gdk_pixbuf_new_from_file("/tmp/llk_HowToPlay.jpg", NULL);
      remove("/tmp/llk_HowToPlay.jpg");
      if (rule_pixbuf == NULL) {
        label = gtk_label_new(_("Read HowToPlay.jpg into pixbuf error."));
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), label, TRUE, TRUE,
                           0);
        gtk_widget_show(label);
      } else {
        image = gtk_image_new_from_pixbuf(rule_pixbuf);
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), image, TRUE, TRUE,
                           0);
        gtk_widget_show(image);
      }
    }
  } else {
    image = gtk_image_new_from_pixbuf(rule_pixbuf);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), image, TRUE, TRUE, 0);
    gtk_widget_show(image);
  }
  button = gtk_dialog_add_button(GTK_DIALOG(dialog), _("Close"),
                                 GTK_RESPONSE_ACCEPT);
  gtk_widget_show(button);
  gtk_widget_grab_focus(button);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}
