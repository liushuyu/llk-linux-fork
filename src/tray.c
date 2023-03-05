/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <eggtrayicon.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <tray.h>

gboolean llk_tray_button_press_event_cb(GtkWidget *button,
                                        GdkEventButton *event, LlkTray *tray) {
  g_return_val_if_fail(tray, FALSE);
  g_return_val_if_fail((event->type == GDK_BUTTON_PRESS),
                       FALSE); /* ignore double-click or any others */

  switch (event->button) {
  case LEFT_BUTTON:
    (*(tray->show_hide_call_back))(button, (gpointer)tray);
    break;
  case MIDDLE_BUTTON:
    break;
  case RIGHT_BUTTON:
    /* popup menu */
    gtk_menu_popup(GTK_MENU(tray->menus), NULL, NULL, NULL, NULL, event->button,
                   event->time);
    break;
  default:
    return FALSE;
  }
  return TRUE;
}

GtkWidget *load_image(const gchar *filename) {
  GtkWidget *image;
  GdkPixbuf *pixbuf;

  pixbuf = gdk_pixbuf_new_from_file(GCN_ICON, NULL);
  if (!pixbuf) {
    image = gtk_image_new_from_stock(GTK_STOCK_HOME, GTK_ICON_SIZE_MENU);
  } else {
    image = gtk_image_new_from_pixbuf(pixbuf);
  }

  return image;
}

void llk_create_tray(LlkTray *tray) {
  GtkWidget *image;
  GtkWidget *event_box;
  GtkTooltips *tooltips;
  EggTrayIcon *tray_icon;

  tooltips = gtk_tooltips_new();
  tray_icon = egg_tray_icon_new("llk tray");
  event_box = gtk_event_box_new();
  gtk_container_add(GTK_CONTAINER(tray_icon), event_box);
  g_signal_connect(G_OBJECT(event_box), "button-press-event",
                   G_CALLBACK(llk_tray_button_press_event_cb), tray);
  gtk_tooltips_set_tip(tooltips, event_box,
                       _("llk_linux\nLian Lian Kan,Version 2.2.\n"), NULL);

  image = load_image(GCN_ICON);
  gtk_container_add(GTK_CONTAINER(event_box), image);

  gtk_widget_show_all(GTK_WIDGET(tray_icon));

  return;
}
