/***************************************************************************
 *            main.h
 *
 *  Fri Sep 23 08:46:05 2005
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
 
#ifndef __LLK_MAIN_H
#define __LLK_MAIN_H

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <stdio.h>
#include <strings.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
// #include <esd.h>
#include <locale.h>
#include <gdk/gdkkeysyms.h>
#include <pthread.h>
/* local headers */
#include <llk_algorithm.h>
#include <llk_about.h>
#include <pak.h>
#include <create_pak.h>
#include <llk_inifile.h>
#include <tray.h>

#define UI_FIXED_START_DRAW_LEFT 120   /* 3*(UI_BACK_WIDTH-UI_BACK_BORDER_1) */
#define UI_FIXED_START_DRAW_TOP  30    /* better if it equal UI_BACK_HEIGHT,but a little more than UI_BACK_HEIGHT/2 is OK also. */
#define UI_BACK_WIDTH            46
#define UI_BACK_HEIGHT           56
#define UI_BACK_BORDER_1         6
#define UI_BACK_BORDER_2         6
#define UI_IMAGE_SIZE            32
#define MAX_PATH_LENGTH          300

struct UiTop{
	GtkWidget *label_difficulty;
	GtkWidget *label_life;
	GtkWidget *label_level;
	GtkWidget *label_hint;
	GtkWidget *label_change_type;
	GtkWidget *label_score;
	GtkWidget *progress_bar;
};
struct UiTop ui_top;

GdkPoint ui_point1,ui_point2;
GtkWidget *ui_drawingarea;  /*Pointer to the Drewing area*/
static GdkPixmap *ui_double_pixmap = NULL;  /* Background pixmap of the Drawing srea */
GtkCheckMenuItem *item_use_mycards;
struct UiMenuItem{
	GtkMenuItem      *themes;
	GtkCheckMenuItem *background_music;
	GtkCheckMenuItem *sound_effect; 
	GtkCheckMenuItem *background_picture;
	GtkRadioMenuItem *current_theme;
};
struct UiMenuItem ui_menu_item;
gint time_remain;
gint timer_handle;

void get_main_menu( GtkWidget *window, GtkWidget **menubar);

static void print_hello( GtkWidget *w,gpointer   data );  /*test function*/
void        ui_about(GtkWidget *w,gpointer data){show_about();}
void        ui_rule(GtkWidget *w,gpointer data){show_rule();}
gboolean    ui_drawingarea_clicked(GtkWidget *fixed, GdkEventButton *event);
void        ui_drawingarea_draw_bg(gint choice);
void        ui_game_begin(GtkWidget *w,gpointer data);
void        ui_game_giveup(GtkWidget *w,gpointer data);
gboolean    ui_game_init(void);
gboolean    ui_replace_image(GdkPoint p1,GdkPoint p2);
gboolean    ui_redraw_images(void);
void        ui_game_next_level(void);
void        ui_game_shuffle(GtkWidget *w,gpointer data);
void        ui_game_cheat(GtkWidget *w,gpointer data);
void        ui_game_change(GdkPoint p1, GdkPoint p2);
void        ui_game_over(gboolean success);
void        ui_game_pause(void);
gboolean    progress_timeout(gpointer value);
void        ui_refresh_top(void);
gint        ui_get_time_limited(void);
void        ui_game_hint( GtkWidget *w,gpointer   data );
void        ui_link(GdkPoint p1, GdkPoint p2);
void		ui_hide_window (GtkWidget *w, gpointer data);
/*Function for Save and Read User Settings*/
gboolean ui_load_ini_pak(gchar **message);
IniFile *   ui_ini;
struct PakInfo{
  gint back_num;
  gint sound_num;
  gint music_num;
};
struct PakInfo pak_info;
struct UiPixbuf{
  GdkPixbuf *cardimages;
  GdkPixbuf *cardbacks;
  gint      cardback_choice;
  GdkPixbuf *vertical;
  GdkPixbuf *horizon;
  GdkPixbuf *logo;
  GdkPixbuf *pause;
  GdkPixbuf *mainback;
  GdkPixbuf *randomback;
  gint      randomback_choice;
};
struct UiPixbuf ui_pixbuf;
GRand *ui_rand;

void ui_use_m_s_bg( GtkWidget *w,gpointer   data );
void radio_item_on_clicked( GtkWidget *w, gpointer   data );
gboolean ui_save_game_data(void);
gboolean ui_read_game_data(void);
void ui_input_string(gchar *str1,gchar *str2,gint max_length);
void ui_record_score(gboolean view);
void ui_view_score( GtkWidget *w,gpointer data);
void ui_theme_editor( GtkWidget *w,gpointer   data ); 

gint esd_fd; /* handle of esd sound */
void ui_play(const gchar *name)
{
  gchar *filename = NULL;
  filename = g_strdup_printf("%s/%s/%s",PACKAGE_DATA_DIR,PACKAGE,name);
  // if (esd_fd>=0)
  //   esd_play_file(NULL,filename,0);
  g_free (filename);
}

/* on show call back functions */
void ui_game_on_show (GtkWidget *, gpointer);
void ui_functions_on_show (GtkWidget *, gpointer);
void ui_setting_on_show (GtkWidget *, gpointer);
/*BE CAREFULL!!!
  you shounld check the STATUS of the game,and if the game in runing,you can use Hint and Wash function
*/
struct LinkPoint{
	gint x;
	gint y;
	gint direction; /* 1:up, 2:down, 3:left, 4:right */
	gint frame;
};
#endif
