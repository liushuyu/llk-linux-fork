/***************************************************************************
 *            create_pak.h
 *
 *  Fri Sep 23 09:00:02 2005
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
 
#ifndef __CREATE_PAK
#define __CREATE_PAK
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <pak.h>
extern GtkWidget *pak_dialog,*pak_entry_compilation,*pak_entry_output,*pak_entry_input,*pak_entry_extract;
void create_pak_dialog(void);
void on_browse(gpointer data);
void on_ok_clicked(gpointer data);
void on_cancel_clicked(gpointer data);
#endif
