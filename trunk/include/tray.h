
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
 
#ifndef _TRAY__H
#define _TRAY__H

#include <config.h>
G_BEGIN_DECLS


/* main window status */
enum
{
	SHOW = 0,
	HIDDEN
};

/* mouse button */
enum
{
	LEFT_BUTTON = 1,
	MIDDLE_BUTTON = 2,
	RIGHT_BUTTON = 3
};

typedef struct _llk_tray LlkTray;

struct _llk_tray
{
	GtkWidget *window_main;
	void (* show_hide_call_back)(GtkWidget *w, gpointer data);
	int status;

	GtkUIManager *ui;
	GtkActionGroup *actions;
	GtkWidget *menus;
};

/* tray icon display in notification arear */
#define GCN_ICON PACKAGE_PIXMAPS_DIR "/llk_linux.png"

void llk_create_tray (LlkTray * tray);
gboolean llk_tray_button_press_event_cb (GtkWidget * button,
				     GdkEventButton * event,
				     LlkTray * tray);

G_END_DECLS

#endif /* _TRAY_H */
