/***************************************************************************
 *            main.c
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
#include <config.h>
#include <main.h>

/*
  creat menus
*/
void
get_main_menu( GtkWidget *window, GtkWidget **menubar)
{
	GtkAccelGroup *accel_group;
 	GtkWidget *menu1,*menu2,*menu3,*menuitem,*rootmenu;
 	accel_group = gtk_accel_group_new();
 	gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);
	*menubar = gtk_menu_bar_new();
	
	menu1 = gtk_menu_new();	/*Game*/
		menu2 = gtk_menu_new();		/*Single*/
			menuitem = gtk_menu_item_new_with_mnemonic(_("_Easy"));
			gtk_menu_shell_append(GTK_MENU_SHELL(menu2),menuitem);
 			gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_F1, 0, GTK_ACCEL_VISIBLE);
			g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_game_begin),(gpointer)1);
			menuitem = gtk_menu_item_new_with_mnemonic(_("_Normal"));
			gtk_menu_shell_append(GTK_MENU_SHELL(menu2),menuitem);
			gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_F2, 0, GTK_ACCEL_VISIBLE);
			g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_game_begin),(gpointer)2);
			menuitem = gtk_menu_item_new_with_mnemonic(_("_Hard"));
			gtk_menu_shell_append(GTK_MENU_SHELL(menu2),menuitem);
			gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_F3, 0, GTK_ACCEL_VISIBLE);
			g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_game_begin),(gpointer)3);
			menuitem = gtk_separator_menu_item_new();
			gtk_menu_shell_append(GTK_MENU_SHELL(menu2),menuitem);
			menuitem = gtk_menu_item_new_with_mnemonic(_("_Resume"));
			gtk_menu_shell_append(GTK_MENU_SHELL(menu2),menuitem);
			gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_F4, 0, GTK_ACCEL_VISIBLE);
			g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_game_begin),(gpointer)4);
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Single"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem),menu2);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
		menu2 = gtk_menu_new();
			menuitem = gtk_menu_item_new_with_mnemonic(_("_Easy"));
			gtk_menu_shell_append(GTK_MENU_SHELL(menu2),menuitem);
			g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(print_hello),(gpointer)1);
			menuitem = gtk_menu_item_new_with_mnemonic(_("_Normal"));
			gtk_menu_shell_append(GTK_MENU_SHELL(menu2),menuitem);
			g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(print_hello),(gpointer)2);
			menuitem = gtk_menu_item_new_with_mnemonic(_("_Hard"));
			gtk_menu_shell_append(GTK_MENU_SHELL(menu2),menuitem);
			g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(print_hello),(gpointer)3);
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Two"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem),menu2);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	/* Two not available*/
	gtk_widget_set_sensitive (GTK_WIDGET (menuitem), FALSE);
		menu2 = gtk_menu_new();
			menu3 = gtk_menu_new();
			menuitem = gtk_menu_item_new_with_mnemonic(_("_Easy"));
			gtk_menu_shell_append(GTK_MENU_SHELL(menu3),menuitem);
			g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(print_hello),(gpointer)1);
			menuitem = gtk_menu_item_new_with_mnemonic(_("_Normal"));
			gtk_menu_shell_append(GTK_MENU_SHELL(menu3),menuitem);
			g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(print_hello),(gpointer)2);
			menuitem = gtk_menu_item_new_with_mnemonic(_("_Hard"));
			gtk_menu_shell_append(GTK_MENU_SHELL(menu3),menuitem);
			g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(print_hello),(gpointer)3);
		menuitem = gtk_menu_item_new_with_mnemonic(_("_Server"));
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem),menu3);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu2),menuitem);
		menuitem = gtk_menu_item_new_with_mnemonic(_("_Client"));
		gtk_menu_shell_append(GTK_MENU_SHELL(menu2),menuitem);
		g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(print_hello),(gpointer)0);
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Network"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem),menu2);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	/* Network not available */
	gtk_widget_set_sensitive (GTK_WIDGET (menuitem), FALSE);
	menuitem = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Giveup"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_F12, 0, GTK_ACCEL_VISIBLE);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_game_giveup),(gpointer)0);
	menuitem = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	menuitem = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(gtk_main_quit),(gpointer)0);
	rootmenu = gtk_menu_item_new_with_mnemonic(_("_Game"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),menu1);
	gtk_menu_shell_append(GTK_MENU_SHELL(*menubar),rootmenu);
	g_signal_connect (G_OBJECT (menu1), "show", G_CALLBACK (ui_game_on_show), NULL);
	/*============================================================*/
	menu1 = gtk_menu_new();
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Hint"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_F5, 0, GTK_ACCEL_VISIBLE);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_game_hint),(gpointer)0);
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Shuffle"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_F6, 0, GTK_ACCEL_VISIBLE);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_game_shuffle),(gpointer)0);
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Pause/Proceed"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_F7, 0, GTK_ACCEL_VISIBLE);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_game_pause),(gpointer)0);
	menuitem = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	menuitem = gtk_menu_item_new_with_mnemonic(_("H_ide"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_Escape, 0, GTK_ACCEL_VISIBLE);
	/*
	  Hide menuitem's activeate event is connected in the main function, not here.
	  g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_game_giveup),(gpointer)0);
	 */
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Theme Edit Tools"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_theme_editor),(gpointer)0);
	rootmenu = gtk_menu_item_new_with_mnemonic(_("_Functions"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),menu1);
	gtk_menu_shell_append(GTK_MENU_SHELL(*menubar),rootmenu);
	g_signal_connect (G_OBJECT (menu1), "show", G_CALLBACK (ui_functions_on_show), NULL);
	/*============================================================*/
	menu1 = gtk_menu_new();
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Themes"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	ui_menu_item.themes = GTK_MENU_ITEM (menuitem);
	ui_menu_item.background_music = GTK_CHECK_MENU_ITEM (gtk_check_menu_item_new_with_mnemonic(_("_Music")));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),GTK_WIDGET (ui_menu_item.background_music));
	g_signal_connect(G_OBJECT(ui_menu_item.background_music),"activate",G_CALLBACK(ui_use_m_s_bg),(gpointer)0);
	ui_menu_item.sound_effect = GTK_CHECK_MENU_ITEM (gtk_check_menu_item_new_with_mnemonic(_("_Sound")));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1), GTK_WIDGET (ui_menu_item.sound_effect));
	g_signal_connect(G_OBJECT(ui_menu_item.sound_effect),"activate",G_CALLBACK(ui_use_m_s_bg),(gpointer)1);
	ui_menu_item.background_picture = GTK_CHECK_MENU_ITEM (gtk_check_menu_item_new_with_mnemonic(_("_Background Picture")));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1), GTK_WIDGET (ui_menu_item.background_picture));
	g_signal_connect(G_OBJECT(ui_menu_item.background_picture),"activate",G_CALLBACK(ui_use_m_s_bg),(gpointer)2);
	menuitem = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Cheat"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_F8, 0, GTK_ACCEL_VISIBLE);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_game_cheat),(gpointer)0);
	rootmenu = gtk_menu_item_new_with_mnemonic(_("_Setting"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),menu1);
	gtk_menu_shell_append(GTK_MENU_SHELL(*menubar),rootmenu);
	g_signal_connect (G_OBJECT (menu1), "show", G_CALLBACK (ui_setting_on_show), NULL);
	/*============================================================*/
	menu1 = gtk_menu_new();
	menuitem = gtk_menu_item_new_with_mnemonic(_("_View Scores"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	gtk_widget_add_accelerator (menuitem, "activate", accel_group,GDK_F9, 0, GTK_ACCEL_VISIBLE);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_view_score),(gpointer)0);
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Internet Scores"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	/* Internet score not available */
	gtk_widget_set_sensitive (GTK_WIDGET (menuitem), FALSE);
	rootmenu = gtk_menu_item_new_with_mnemonic(_("S_core"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),menu1);
	gtk_menu_shell_append(GTK_MENU_SHELL(*menubar),rootmenu);
	/*============================================================*/
	menu1 = gtk_menu_new();
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Rules"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_rule),(gpointer)0);
	menuitem = gtk_menu_item_new_with_mnemonic(_("_Author"));
	gtk_menu_shell_append(GTK_MENU_SHELL(menu1),menuitem);
	g_signal_connect(G_OBJECT(menuitem),"activate",G_CALLBACK(ui_about),(gpointer)0);
	rootmenu = gtk_menu_item_new_with_mnemonic(_("_About"));
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),menu1);
	gtk_menu_shell_append(GTK_MENU_SHELL(*menubar),rootmenu);
	/*============================================================*/
	gtk_widget_show_all(*menubar);
}

/*
  empty call back funtion, use for testing
  no need to translate these strings
*/
static void
print_hello( GtkWidget *w, gpointer   data )
{
  g_print ("data returned %d \n",GPOINTER_TO_INT(data));
}
void 
ui_hide_window (GtkWidget *w, gpointer data)
{
	LlkTray *tray = (LlkTray *)data;
	/* show/hidden man window */
	if (tray->status == SHOW)
	{
		/* Pause the game */
		if(algorithm_game.status == ALGORITHM_GAME_RUN)
			ui_game_pause ();
		tray->status = HIDDEN;
		gtk_widget_hide_all (GTK_WIDGET (tray->window_main));
	}
	else
	{
		tray->status = SHOW;
		gtk_widget_show_all (GTK_WIDGET (tray->window_main));
	}
}
/*
 * set sensitive of the Game menu
 */
void
ui_game_on_show (GtkWidget *w, gpointer data)
{
	gtk_widget_set_sensitive (g_list_nth_data (GTK_MENU(w)->menu_shell.children,0),
		algorithm_game.status == ALGORITHM_GAME_STOP);
	gtk_widget_set_sensitive (g_list_nth_data (GTK_MENU(w)->menu_shell.children,4),
		algorithm_game.status != ALGORITHM_GAME_STOP);
}

/*
 * set sensitive of the Functions menu
 */
void 
ui_functions_on_show (GtkWidget *w, gpointer data)
{
	gtk_widget_set_sensitive (g_list_nth_data (GTK_MENU(w)->menu_shell.children,0),
		algorithm_game.status == ALGORITHM_GAME_RUN);
	gtk_widget_set_sensitive (g_list_nth_data (GTK_MENU(w)->menu_shell.children,1),
		algorithm_game.status == ALGORITHM_GAME_RUN);
	gtk_widget_set_sensitive (g_list_nth_data (GTK_MENU(w)->menu_shell.children,2),
		algorithm_game.status != ALGORITHM_GAME_STOP);
}

/*
 * set sensitive of the Setting menu
 */
void
ui_setting_on_show (GtkWidget *w, gpointer data)
{
	//g_print ("menu setting on show.\n");
}
/*
  replace with new image at (i,j)
*/
gboolean 
ui_replace_image(GdkPoint p1,GdkPoint p2)
{
  GdkRectangle update_rect;

  /*according to data in algorithm_game and the selected position, redraw the image at (i,j)
    this function is modified from ui_game_begin function //(algorithm_game.data[p1.x][p1.y] - 1)
  */
  /* Draw card back image */
  gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.cardbacks,ui_double_pixmap,
        0,(ui_pixbuf.cardback_choice>=5?1:ui_pixbuf.cardback_choice+1)*UI_BACK_HEIGHT,
        UI_FIXED_START_DRAW_LEFT + (p1.y - algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1),
        UI_FIXED_START_DRAW_TOP + p1.x*(UI_BACK_HEIGHT - UI_BACK_BORDER_2),
		UI_BACK_WIDTH-UI_BACK_BORDER_1,UI_BACK_HEIGHT-UI_BACK_BORDER_2,
        GDK_PIXBUF_ALPHA_BILEVEL,128,
        GDK_RGB_DITHER_NORMAL, 0, 0);
  /*gdk_draw_rectangle (ui_double_pixmap,
                      ui_drawingarea->style->black_gc,
                      TRUE,
					  UI_FIXED_START_DRAW_LEFT + (p1.y - algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1),
        			  UI_FIXED_START_DRAW_TOP + p1.x*(UI_BACK_HEIGHT - UI_BACK_BORDER_2),
					  UI_BACK_WIDTH-UI_BACK_BORDER_1,UI_BACK_HEIGHT-UI_BACK_BORDER_2);*/
  /* Draw card's front image */
  gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.cardimages,ui_double_pixmap,
        (algorithm_game.data[p1.x][p1.y] - 1)*UI_IMAGE_SIZE,0,
        UI_FIXED_START_DRAW_LEFT + (p1.y - algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1) + 
               (UI_BACK_WIDTH-UI_BACK_BORDER_1-UI_IMAGE_SIZE)/2,
        UI_FIXED_START_DRAW_TOP + p1.x*(UI_BACK_HEIGHT - UI_BACK_BORDER_2)+
               (UI_BACK_HEIGHT-UI_BACK_BORDER_2-UI_IMAGE_SIZE)/2,
        UI_IMAGE_SIZE,UI_IMAGE_SIZE,
        GDK_PIXBUF_ALPHA_BILEVEL,128,
        GDK_RGB_DITHER_NORMAL, 0, 0);
  update_rect.x = UI_FIXED_START_DRAW_LEFT + (p1.y - algorithm_game.difficulty)*(UI_BACK_WIDTH - UI_BACK_BORDER_1);
  update_rect.y = UI_FIXED_START_DRAW_TOP + p1.x*(UI_BACK_HEIGHT - UI_BACK_BORDER_2);
  update_rect.width = UI_BACK_WIDTH-UI_BACK_BORDER_1;
  update_rect.height = UI_BACK_HEIGHT-UI_BACK_BORDER_2;
  gtk_widget_draw (ui_drawingarea, &update_rect);
  
  if(p2.x != -1 && p2.y != -1)
  {
    /* Draw card back image */
    gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.cardbacks,ui_double_pixmap,
          0,(ui_pixbuf.cardback_choice>=5?1:ui_pixbuf.cardback_choice+1)*UI_BACK_HEIGHT,
          UI_FIXED_START_DRAW_LEFT + (p2.y - algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1),
          UI_FIXED_START_DRAW_TOP + p2.x*(UI_BACK_HEIGHT - UI_BACK_BORDER_2),
          UI_BACK_WIDTH-UI_BACK_BORDER_1,UI_BACK_HEIGHT-UI_BACK_BORDER_2,
          GDK_PIXBUF_ALPHA_BILEVEL,128,
          GDK_RGB_DITHER_NORMAL, 0, 0);
    /*gdk_draw_rectangle (ui_double_pixmap,
                      ui_drawingarea->style->black_gc,
                      TRUE,
					  UI_FIXED_START_DRAW_LEFT + (p2.y - algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1),
        			  UI_FIXED_START_DRAW_TOP + p2.x*(UI_BACK_HEIGHT - UI_BACK_BORDER_2),
					  UI_BACK_WIDTH-UI_BACK_BORDER_1,UI_BACK_HEIGHT-UI_BACK_BORDER_2);*/
    /* Draw card's front image */
    gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.cardimages,ui_double_pixmap,
          (algorithm_game.data[p2.x][p2.y] - 1)*UI_IMAGE_SIZE,0,
          UI_FIXED_START_DRAW_LEFT + (p2.y - algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1) + 
                 (UI_BACK_WIDTH-UI_BACK_BORDER_1-UI_IMAGE_SIZE)/2,
          UI_FIXED_START_DRAW_TOP + p2.x*(UI_BACK_HEIGHT - UI_BACK_BORDER_2)+
                 (UI_BACK_HEIGHT-UI_BACK_BORDER_2-UI_IMAGE_SIZE)/2,
          UI_IMAGE_SIZE,UI_IMAGE_SIZE,
          GDK_PIXBUF_ALPHA_BILEVEL,128,
          GDK_RGB_DITHER_NORMAL, 0, 0);
    update_rect.x = UI_FIXED_START_DRAW_LEFT + (p2.y - algorithm_game.difficulty)*(UI_BACK_WIDTH - UI_BACK_BORDER_1);
    update_rect.y = UI_FIXED_START_DRAW_TOP + p2.x*(UI_BACK_HEIGHT - UI_BACK_BORDER_2);
    update_rect.width = UI_BACK_WIDTH-UI_BACK_BORDER_1;
    update_rect.height = UI_BACK_HEIGHT-UI_BACK_BORDER_2;
    gtk_widget_draw (ui_drawingarea, &update_rect);
  }
  return TRUE;
}

/*
  redraw all card images according to datas in algorithm_game
*/
gboolean 
ui_redraw_images(void)
{
  GdkRectangle update_rect;
  gint i,j;
  /*redraw background picture*/
  ui_drawingarea_draw_bg(1);
  /*according to the data in the algorithm_game,and selected position, redraw all card images
    modified from ui_game_begin function*/
    for(i=0;i<algorithm_game.row;i++)
    {
     	for(j=0;j<algorithm_game.col;j++)
    	{
        	if(algorithm_game.data[i][j] > 0)
	    	{
          	/* Draw card back image */
          	gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.cardbacks,ui_double_pixmap,
                0,ui_pixbuf.cardback_choice*UI_BACK_HEIGHT,
                UI_FIXED_START_DRAW_LEFT + (j - algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1),
                UI_FIXED_START_DRAW_TOP + i*(UI_BACK_HEIGHT - UI_BACK_BORDER_2),
				UI_BACK_WIDTH,UI_BACK_HEIGHT,
                GDK_PIXBUF_ALPHA_BILEVEL,128,
                GDK_RGB_DITHER_NORMAL, 0, 0);
          	/* Draw card's front image */
          	gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.cardimages,ui_double_pixmap,
                (algorithm_game.data[i][j] - 1)*UI_IMAGE_SIZE,0,
                UI_FIXED_START_DRAW_LEFT + (j - algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1) + 
                       (UI_BACK_WIDTH-UI_BACK_BORDER_1-UI_IMAGE_SIZE)/2,
                UI_FIXED_START_DRAW_TOP + i*(UI_BACK_HEIGHT - UI_BACK_BORDER_2)+
                       (UI_BACK_HEIGHT-UI_BACK_BORDER_2-UI_IMAGE_SIZE)/2,
                UI_IMAGE_SIZE,UI_IMAGE_SIZE,
                GDK_PIXBUF_ALPHA_BILEVEL,128,
                GDK_RGB_DITHER_NORMAL, 0, 0);
	    	}
     	}
    } 
    
    /*emerge an widget's redraw singal*/
  update_rect.x = 0;
  update_rect.y = 0;
  update_rect.width = ui_drawingarea->allocation.width;
  update_rect.height = ui_drawingarea->allocation.height;
  gtk_widget_draw (ui_drawingarea, &update_rect);
    
  return TRUE;  
}
/*
  the back call function of the click event of the drawing area
*/
gboolean
ui_drawingarea_clicked(GtkWidget *window, GdkEventButton *event)
{
  if( algorithm_game.status == ALGORITHM_GAME_RUN )
  {
    if(event->type == GDK_BUTTON_PRESS && event->button != 2)
    {
      gint i,j;
      if(event->button == 1) /*Mouse, Left button*/
      {
        if( event->x > UI_FIXED_START_DRAW_LEFT - algorithm_game.difficulty*(UI_BACK_WIDTH-UI_BACK_BORDER_1) &&
            event->x < UI_FIXED_START_DRAW_LEFT +(algorithm_game.col-algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1))
        if( event->y > UI_FIXED_START_DRAW_TOP &&
            event->y < UI_FIXED_START_DRAW_TOP + algorithm_game.row*(UI_BACK_HEIGHT-UI_BACK_BORDER_2) )
        {
          j = (event->x - UI_FIXED_START_DRAW_LEFT + algorithm_game.difficulty*(UI_BACK_WIDTH-UI_BACK_BORDER_1))/(UI_BACK_WIDTH-UI_BACK_BORDER_1) ;
          i = (event->y - UI_FIXED_START_DRAW_TOP)/(UI_BACK_HEIGHT-UI_BACK_BORDER_2);
          /*g_print("i: %d, j: %d\n",i,j);*/
	  if(algorithm_game.data[i][j] == 0)
	  {return FALSE;}
          if(ui_point1.x > -1)  /*there is a selected card already*/
          {
            if(ui_point1.x != i || ui_point1.y != j)
            {
              ui_point2.x = i; ui_point2.y = j;
	      /*look if the two selected card could be linked or not, if yes,delete
			them,if no,cancel the selected status*/
	      if(algorithm_can_link(ui_point1,ui_point2,NULL,NULL))
	      {
	        gint tmp;
		gchar *message = NULL;
		/*g_print("This pairs can link.\n");*/
		ui_link(ui_point1, ui_point2);
		algorithm_link(ui_point1,ui_point2);
		/*algorithm_link,must be puted after ui_link function, because ui_link need 
		  to judge the link path,and before this,the data must not be modified*/
		progress_timeout(GINT_TO_POINTER(1)); /*add 1 second after every link action*/
		message = g_strdup_printf ("%d",algorithm_game.score);
        gtk_label_set_text(GTK_LABEL(ui_top.label_score),message);
		g_free(message);
		if(gtk_check_menu_item_get_active(ui_menu_item.sound_effect))
		{
			pthread_t id;
			pthread_attr_t attr;
			int ret;
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
			ret=pthread_create(&id,&attr,(void *) ui_play,"Link.wav");
			if(ret!=0)
			{
				g_print (_("Create pthread error!\n"));
				exit (1);
			}
		}
		/*judge if current situation of all the cards has a solution
		  ATTENTION: must judge after the game_change funtion
		*/
		ui_game_change(ui_point1,ui_point2);
		tmp = algorithm_game_no_solution();
		switch(tmp)
		{
		  case 1:/*No solution,but there still some cards*/
		         ui_game_shuffle(NULL,NULL); /*shuffle cards*/
		         break;
		  case 0:/*do nothing*/
			 break;
		  case 2: /*there are no cards,the stage(or Level) is over*/
		  	 ui_game_next_level();
			 break;
		}
	      }
	      else
	      {
                ui_redraw_images();  /*ui_redraw_images, this function does not
									  care the selected status*/
				ui_point1.x = -1; ui_point1.y = -1;
				/*restore the card image at (i,j)*/
				if(gtk_check_menu_item_get_active(ui_menu_item.sound_effect))
				{
					pthread_t id;
					pthread_attr_t attr;
					int ret;
					pthread_attr_init(&attr);
					pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
					ret=pthread_create(&id,&attr,(void *) ui_play,"CanntLink.wav");
					if(ret!=0)
					{
						g_print (_("Create pthread error!\n"));
						exit (1);
					}
				}
	      }
            }
            else /*click the card that has already been selected,so cancel the selected status*/
            {
            	ui_point1.x = -1; ui_point1.y = -1;
            	ui_redraw_images();
            	/*replace the card image at (i,j)*/
            	if(gtk_check_menu_item_get_active(ui_menu_item.sound_effect))
				{
					pthread_t id;
					pthread_attr_t attr;
					int ret;
					pthread_attr_init(&attr);
					pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
					ret=pthread_create(&id,&attr,(void *) ui_play,"Cancle.wav");
					if(ret!=0)
					{
						g_print (_("Create pthread error!\n"));
						exit (1);
					}
				}
            }
          }
          else /*there is no selected cards*/
          {
            ui_point1.x = i; ui_point1.y = j;
	    ui_point2.x=-1;ui_point2.y=-1;
            ui_replace_image(ui_point1,ui_point2);
            /*replace card image at (i,j)*/
            if(gtk_check_menu_item_get_active(ui_menu_item.sound_effect))
			{
				pthread_t id;
				pthread_attr_t attr;
				int ret;
				pthread_attr_init(&attr);
				pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
				ret=pthread_create(&id,&attr,(void *) ui_play,"Click.wav");
				if(ret!=0)
				{
					g_print (_("Create pthread error!\n"));
					exit (1);
				}
			}
          }
        }
      }
      else  /* if(event->button == 3)*/ /*Mouse,Right button*/
      {
        if(ui_point1.x > -1)  /*cancel the selected status*/
		{
	  		ui_redraw_images();
	  		ui_point1.x = -1; ui_point1.y = -1;
	  		if(gtk_check_menu_item_get_active(ui_menu_item.sound_effect))
			{
				pthread_t id;
				pthread_attr_t attr;
				int ret;
				pthread_attr_init(&attr);
				pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
				ret=pthread_create(&id,&attr,(void *) ui_play,"Cancle.wav");
				if(ret!=0)
				{
					g_print (_("Create pthread error!\n"));
					exit (1);
				}
			}
		}
      }
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
  else
  {
    return FALSE;
  }
}

/*
  darw the background picture of the drawingarea
*/
void 
ui_drawingarea_draw_bg(gint choice)
{
  gint width,height,pixmap_width,pixmap_height;
  /* Empty all images */
  gdk_drawable_get_size(GDK_DRAWABLE(ui_double_pixmap),&pixmap_width,&pixmap_height);
  gdk_draw_rectangle (ui_double_pixmap,
                      ui_drawingarea->style->black_gc,
                      TRUE,0, 0,pixmap_width,pixmap_height);
  if(choice == 0)/* ui_game_init call this function, draw mainback*/
  {
    g_assert(ui_pixbuf.mainback != NULL);
    width = gdk_pixbuf_get_width(ui_pixbuf.mainback);
    height = gdk_pixbuf_get_height(ui_pixbuf.mainback);
    gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.mainback,ui_double_pixmap,
                                        0,0,(pixmap_width - width)/2,(pixmap_height - height)/2,width,height,
                                        GDK_PIXBUF_ALPHA_BILEVEL,128,
                                        GDK_RGB_DITHER_NORMAL, 0, 0);
    return;
  }
  /* user set to no drawing background pictures */
  if(!gtk_check_menu_item_get_active(ui_menu_item.background_picture))
  {
    return;
  }
  /* user set to draw bg pictures,but there are no bg picture files in pak */
  if(ui_pixbuf.randomback_choice == 0)
  {
    //g_assert(ui_pixbuf.mainback != NULL);
    width = gdk_pixbuf_get_width(ui_pixbuf.mainback);
    height = gdk_pixbuf_get_height(ui_pixbuf.mainback);
    gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.mainback,ui_double_pixmap,
                                        0,0,(pixmap_width - width)/2,(pixmap_height - height)/2,width,height,
                                        GDK_PIXBUF_ALPHA_BILEVEL,128,
                                        GDK_RGB_DITHER_NORMAL, 0, 0);
    return;
  }
  else
  {
    g_assert(ui_pixbuf.randomback != NULL);
    width = gdk_pixbuf_get_width(ui_pixbuf.randomback);
    height = gdk_pixbuf_get_height(ui_pixbuf.randomback);
    gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.randomback,ui_double_pixmap,
        				0,0,(pixmap_width - width)/2,(pixmap_height - height)/2,width,height,
        				GDK_PIXBUF_ALPHA_BILEVEL,128,
    					GDK_RGB_DITHER_NORMAL, 0, 0); 
  }
}

/*
  The UI function dealing with the game start process
  data: stand for game diffictulty, but it is based on 1,and the game difficulty is based on 0,BE CARE!!!
*/
void
ui_game_begin(GtkWidget *w,gpointer data)
{
  gint current_diff;
  if(algorithm_game.status != ALGORITHM_GAME_STOP)return;
  if(GPOINTER_TO_INT(data)!=4) /* data = 4 means resume game process */
  {
    /* Read difficulty info from ini file,judge if player can play this difficulty. */
    if(ini_file_read_int(ui_ini, "GAMERECORD", "difficulty", &current_diff))
    {
      if(current_diff<1 || current_diff>3)
      {current_diff=1;}
    }
    else{current_diff=1;}
    if( GPOINTER_TO_INT(data)>current_diff )
    {
      GtkWidget *dialog;
      GtkMessageType type;
      gchar *message = NULL;
  
        switch(GPOINTER_TO_INT(data))
        {
          case 2:
            message = g_strdup(_("You should pass difficulty Easy before you play Normal."));
	        break;
          case 3:
            message = g_strdup(_("You should pass difficulty Normal before you play Hard."));
            break;
        }
        type = GTK_MESSAGE_WARNING;
      dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message);
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);
      g_free(message);
      return;
    }
  }
  
  /*cancel all the selected status*/
  ui_point1.x = -1; ui_point1.y = -1;
  ui_point2.x = -1; ui_point2.y = -1;
  if(GPOINTER_TO_INT(data) == 4)
  {
    if(ui_read_game_data())
    {
      if(algorithm_game.status == ALGORITHM_GAME_RUN)
      {
        /*init the drawing area,include background picture and card images.*/
        ui_redraw_images();
        progress_timeout(GINT_TO_POINTER(1));
      }
      else
      {/* In order to load the paused game,do not add timer,so we return here.*/
        algorithm_game.status = ALGORITHM_GAME_RUN;
		ui_game_pause();
        ui_refresh_top();        
		return; /* Return here. */
      }
    }
    else
    {
      GtkWidget *dialog;
      GtkMessageType type;
      gchar *message = NULL;
      message = g_strdup(_("Read saved game data error,Maybe you have not saved a game before.\n"));
      type = GTK_MESSAGE_WARNING;
      dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message);
      gtk_dialog_run(GTK_DIALOG(dialog));
      gtk_widget_destroy(dialog);
      g_free(message);
      return;
    }
  }
  else
  {
    if(!algorithm_game_begin(data))  /*init the array and other related datas in the algorith_game,ready for start the game.*/
    {
      g_print(_("Call algorithm_game_begin function error.\n"));
      return;
    }
    /*init the drawing area,include background picture and card images.*/
    ui_redraw_images();
    progress_timeout(GINT_TO_POINTER(9999));
  }
  ui_refresh_top();
  timer_handle = gtk_timeout_add(1000,progress_timeout,NULL);
}

/*
  time_out function
  according to my test result,from the time_out call back function be called, to the call back function return,
  the clock is PAUSEED,that is to say,when the game is over,no matter how long you stay on the popup dialog window,
  the clock will not emerge another time out signal
*/
gboolean 
progress_timeout(gpointer pvalue)
{
  gint value = GPOINTER_TO_INT(pvalue);
  
  if(value == 9999)
  {/*full fill the time*/
    time_remain = ui_get_time_limited();
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui_top.progress_bar),1);
    return TRUE;
  }
  else
  {
    if(value != 0)
    {
      time_remain+=value;
      time_remain = time_remain > ui_get_time_limited() ? ui_get_time_limited() : time_remain;
      gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui_top.progress_bar),((double)time_remain/(double)ui_get_time_limited()));
      return TRUE;
    }
    else
    {
      if(time_remain > 0)
      {
        time_remain--;
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui_top.progress_bar),((double)time_remain/(double)ui_get_time_limited()));
	return TRUE;
      }
      else
      {
        /*g_print("Time is out.\n");*/
        ui_game_over(FALSE);
        return FALSE;
      }
    }
  }
}

/*
  init, ready for game starting
*/
gboolean 
ui_game_init(void)
{
  /*deal with UI*/
  GdkRectangle update_rect;
  algorithm_game_init();
  time_remain = 0;
  /*deal with the area above the drawing area*/
  ui_refresh_top();
  /*empty the drawing area,draw the background picture*/
  ui_drawingarea_draw_bg(0);
  /*emerge an widget redraw signal*/
  update_rect.x = 0;
  update_rect.y = 0;
  update_rect.width = ui_drawingarea->allocation.width;
  update_rect.height = ui_drawingarea->allocation.height;
  gtk_widget_draw(ui_drawingarea, &update_rect);  
  return TRUE;
}

/*
  function dealing with game giveup,and game over
*/
void 
ui_game_giveup(GtkWidget *w,gpointer data)
{
 /*shutdown the timing clock*/
  if(timer_handle != 0)gtk_timeout_remove(timer_handle);
  
  /*giveup,do not record the score,so should not call ui_game_over function here.*/
  if(algorithm_game.status != ALGORITHM_GAME_STOP)
  {
    ui_game_init();
  }
  else
  {}
}

/*
  Next Levels
  if the current level is not the last one(NO.10),then,enter the next level
  otherwise,popup a window,on which give a hint that the player have success
  this difficulty,then over the game,waiting for player to choose another difficulty.
*/
void 
ui_game_next_level(void)
{
  if(timer_handle != 0)gtk_timeout_remove(timer_handle);/* remove the timer */
  if( algorithm_game_net_level() )
  {/*switch to the next level*/
    if(gtk_check_menu_item_get_active(ui_menu_item.sound_effect))
	{
		pthread_t id;
		pthread_attr_t attr;
		int ret;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
		ret=pthread_create(&id,&attr,(void *) ui_play,"Win.wav");
		if(ret!=0)
		{
			g_print (_("Create pthread error!\n"));
			exit (1);
		}
	}
    /* get and set next card back, and get and set next background picture */
    ui_pixbuf.cardback_choice = ui_pixbuf.cardback_choice>=5?0:ui_pixbuf.cardback_choice+1;
    if(pak_info.back_num > 0){
      ui_pixbuf.randomback_choice = ui_pixbuf.randomback_choice>pak_info.back_num-1?1:ui_pixbuf.randomback_choice+1;
      /* Extract the bg picture and read it to ui_pixbuf.randomback */
      gchar *bgfilename = NULL;
	  bgfilename = g_strdup_printf ("back%d.jpg",ui_pixbuf.randomback_choice-1);
      if(!ExtractSingleFile(bgfilename)){g_print(_("Failed to extract file:%s.\n"),bgfilename);}
	  g_free (bgfilename);
	  bgfilename = g_strdup_printf ("/tmp/llk_back%d.jpg",ui_pixbuf.randomback_choice-1);
      if(ui_pixbuf.randomback)gdk_pixbuf_unref(ui_pixbuf.randomback); /* Free old randomback pixbuf */
      ui_pixbuf.randomback = gdk_pixbuf_new_from_file(bgfilename,NULL);
      remove(bgfilename);
	  g_free (bgfilename);
      if(ui_pixbuf.randomback == NULL){ui_pixbuf.randomback = ui_pixbuf.mainback;g_print(_("randomback=NULL,Error occored.\n"));}
    }
    else{
      ui_pixbuf.randomback = NULL;
      ui_pixbuf.randomback_choice = 0;
    }
    ui_redraw_images();
    ui_point1.x=-1;
    ui_point1.y=-1;
    progress_timeout(GINT_TO_POINTER(9999));
    ui_refresh_top();
    timer_handle = gtk_timeout_add(1000,progress_timeout,NULL);
  }
  else
  {/*success this difficulty*/
    ui_game_over(TRUE);
  }
}

/*
  shuffle cards
*/
void 
ui_game_shuffle(GtkWidget *w,gpointer data)
{
	if(algorithm_game.status != ALGORITHM_GAME_RUN)
	{return;}
	if(timer_handle != 0)gtk_timeout_remove(timer_handle); /*turn off the timer*/
	if(algorithm_game.life == 0)
	{
		ui_game_over(FALSE);
		return;
	}
	else
	{
		gchar *message = NULL;
		algorithm_game.life--;
		message = g_strdup_printf (_("Life:%d"),algorithm_game.life);
		gtk_label_set_text(GTK_LABEL(ui_top.label_life),message);
		g_free(message);
	}
	algorithm_game_shuffle();
	ui_redraw_images();
	ui_point1.x=-1; 
	ui_point1.y=-1;
	if(gtk_check_menu_item_get_active(ui_menu_item.sound_effect))
	{
		pthread_t id;
		pthread_attr_t attr;
		int ret;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
		ret=pthread_create(&id,&attr,(void *) ui_play,"Shuffle.wav");
		if(ret!=0)
		{
			g_print (_("Create pthread error!\n"));
			exit (1);
		}
	}
	timer_handle = gtk_timeout_add(1000,progress_timeout,NULL);/*turn on the timer*/
}

/*
  game over
*/
void 
ui_game_over(gboolean success)
{
  GtkWidget *dialog;
  GtkMessageType type;
  gchar *message = NULL;
  
   if(success)
  {
    /*popup dialog window*/
    switch(algorithm_game.difficulty)
    {
      case 0:
        message = g_strdup(_("Congratulations,you have success the Easy difficulty,you may play Normal now!"));
        break;
      case 1:
        message = g_strdup(_("Congratulations,you have success the Normal difficulty,you may play Hard now!"));
        break;
      case 2:
        message = g_strdup(_("Congratulations,you have success all the difficulties,I admire you so much..."));
        break;
    }
    ini_file_write_int    (ui_ini, "GAMERECORD", "difficulty", algorithm_game.difficulty+2);
    if(!ini_file_write_file(ui_ini,ui_ini->filename))
    {
       g_print(_("Ini file save error!\n")); 
    }
    type = GTK_MESSAGE_INFO;
  }
  else
  {
    /*popup dialog window*/
    message = g_strdup(_("Success and failure are nothing,just try again!"));
    type = GTK_MESSAGE_WARNING;
  }
	if(gtk_check_menu_item_get_active(ui_menu_item.sound_effect))
	{
		if(success)
		{
			pthread_t id;
			pthread_attr_t attr;
			int ret;
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
			ret=pthread_create(&id,&attr,(void *) ui_play,"Win.wav");
			if(ret!=0)
			{
				g_print (_("Create pthread error!\n"));
				exit (1);
			}
		}
		else
		{
			pthread_t id;
			pthread_attr_t attr;
			int ret;
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
			ret=pthread_create(&id,&attr,(void *) ui_play,"GameOver.wav");
			if(ret!=0)
			{
				g_print (_("Create pthread error!\n"));
				exit (1);
			}
		}
	}
	dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,type,GTK_BUTTONS_OK,message);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  g_free(message);
  /*Record SCORE*/
  ui_record_score(FALSE);
  ui_game_init();
}

/*
  change the image cards' position according to the current level value
  the two cards which can link have already been deleted,so only change the position of these cards left.
*/
void 
ui_game_change(GdkPoint p1, GdkPoint p2)
{
  algorithm_game_change(p1,p2);
  ui_redraw_images();
  ui_point1.x=-1; 
  ui_point1.y=-1;
}

/*
  pause,hide the card images,DO NOT modify the Algorithm_game data values.
  when restore the game,just show these card images.
*/
void 
ui_game_pause(void)
{
  GdkRectangle update_rect;
  gint width,height,pixmap_width,pixmap_height;
  
  if(algorithm_game.status == ALGORITHM_GAME_RUN)
  {
    if(timer_handle != 0)
    {
      gtk_timeout_remove(timer_handle);
      timer_handle = 0;
    }
    gdk_drawable_get_size(GDK_DRAWABLE(ui_double_pixmap),&pixmap_width,&pixmap_height);
    algorithm_game.status = ALGORITHM_GAME_PAUSE;
    /*hide all the images on the drawingarea,then put a picture that stand for the pause status*/
    gdk_draw_rectangle (ui_double_pixmap,
                      ui_drawingarea->style->black_gc,
                      TRUE,
                      0, 0,
                      pixmap_width,
                      pixmap_height);
    if(ui_pixbuf.pause)
    {
      width = gdk_pixbuf_get_width(ui_pixbuf.pause);
      height = gdk_pixbuf_get_height(ui_pixbuf.pause);
      gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.pause,ui_double_pixmap,
             0,0,(pixmap_width - width)/2,(pixmap_height - height)/2,width,height,
             GDK_PIXBUF_ALPHA_BILEVEL,128,
             GDK_RGB_DITHER_NORMAL, 0, 0);
    }
    update_rect.x = 0;
    update_rect.y = 0;
    update_rect.width = ui_drawingarea->allocation.width;
    update_rect.height = ui_drawingarea->allocation.height;
    gtk_widget_draw (ui_drawingarea, &update_rect); 
  }
  else if(algorithm_game.status == ALGORITHM_GAME_PAUSE)
  {
    /*empty all possible selected status*/
    ui_point1.x = -1; ui_point1.y = -1;
    ui_redraw_images();    
    /*redraw the drawingarea*/
    update_rect.x = 0;
    update_rect.y = 0;
    update_rect.width = ui_drawingarea->allocation.width;
    update_rect.height = ui_drawingarea->allocation.height;
    gtk_widget_draw (ui_drawingarea, &update_rect); 
        
    timer_handle = gtk_timeout_add(1000,progress_timeout,NULL); /*turn on the timer*/
    algorithm_game.status = ALGORITHM_GAME_RUN;
  }
}

/*
  refresh the information shown on the top
*/
void 
ui_refresh_top(void)
{
  gchar *message = NULL;
  if(algorithm_game.status != ALGORITHM_GAME_STOP)
  {
    switch(algorithm_game.difficulty)
    {
      case 0:
        message = g_strdup(_("Diff:Easy"));
	break;
      case 1:
        message = g_strdup(_("Diff:Normal"));
	break;
      case 2:
        message = g_strdup(_("Diff:Hard"));
	break;
    }
    gtk_label_set_text(GTK_LABEL(ui_top.label_difficulty),message);
	g_free (message);
    message = g_strdup_printf(_("Lev:%d"),algorithm_game.level);
    gtk_label_set_text(GTK_LABEL(ui_top.label_level),message);
	g_free (message);
    switch(algorithm_game.level)
    {
      case 0:/*no change*/
             message = g_strdup(_("No Change"));
             break;
      case 1:/*move down*/
             message = g_strdup(_("Move Down"));
             break;
      case 2:/*move left*/
             message = g_strdup(_("Move Left"));
             break;
      case 3:/*up down separate*/
             message = g_strdup(_("Up Down Separate"));
             break;
      case 4:/*left right separate*/
             message = g_strdup(_("Left Right Separate"));
             break;
      case 5:/*up down converge*/
             message = g_strdup(_("Up Down Converge"));
             break;
      case 6:/*left right converge*/
             message = g_strdup(_("Left Right Converge"));
             break;
      case 7:/*up leftward,down rightward*/
             message = g_strdup(_("Up left,Down right"));
             break;
      case 8:/*left downward,right upward*/
             message = g_strdup(_("Left down,Right up"));
             break;
      case 9:/*disperse from center*/
             message = g_strdup(_("DisperseFromCenter"));
             break;
      case 10:/*centralize*/
             message = g_strdup(_("Centralize"));
             break;
      default:
      	     /*assert not reach*/
             break;   
    }
    gtk_label_set_text(GTK_LABEL(ui_top.label_change_type),message);
	g_free (message);
    message = g_strdup_printf("%d",algorithm_game.score);
    gtk_label_set_text(GTK_LABEL(ui_top.label_score),message);
	g_free (message);
    message = g_strdup_printf(_("Life:%d"),algorithm_game.life);
    gtk_label_set_text(GTK_LABEL(ui_top.label_life),message);
	g_free (message);
    message = g_strdup_printf(_("Hint:%d"),algorithm_game.hint);
    gtk_label_set_text(GTK_LABEL(ui_top.label_hint),message);
	g_free (message);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui_top.progress_bar),((double)time_remain/(double)ui_get_time_limited()));
  }
  else
  {
    gtk_label_set_text(GTK_LABEL(ui_top.label_difficulty),_("Diff:"));
    gtk_label_set_text(GTK_LABEL(ui_top.label_level),_("Lev:"));
    gtk_label_set_text(GTK_LABEL(ui_top.label_change_type),_("Change Type:"));
    gtk_label_set_text(GTK_LABEL(ui_top.label_score),"0");
    gtk_label_set_text(GTK_LABEL(ui_top.label_life),_("Life:"));
    gtk_label_set_text(GTK_LABEL(ui_top.label_hint),_("Hint:"));
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui_top.progress_bar),0);    
  }
}

/*
  get the time value limit of the current level
*/
gint 
ui_get_time_limited(void)
{
  if(algorithm_game.difficulty == 2)return 240;
  else return 200; 
}

/*
  Give player a hint
*/
void 
ui_game_hint( GtkWidget *w,gpointer   data )
{
  gint i,j;
  gint k,l;
  gchar *message = NULL;

  if(algorithm_game.status != ALGORITHM_GAME_RUN)return;
  if(algorithm_game.hint == 0)return;
  algorithm_game.hint--;
  message = g_strdup_printf (_("Hint:%d"),algorithm_game.hint);
  gtk_label_set_text(GTK_LABEL(ui_top.label_hint),message);  
  g_free (message);
  /*g_assert(!algorithm_game_no_solution());*/
  /*copy from algorithm_game_no_solution function,modified part of it*/
  for(i=0; i<algorithm_game.row ;i++)
  {
    for(j=0; j<algorithm_game.col ;j++)
    {
      if(algorithm_game.data[i][j] > 0)
      {
	    for(k=i;k<algorithm_game.row;k++)
	    {
	      for(l=0;l<algorithm_game.col;l++)
	      {
	        if(k == i && l == j)continue;  /*exclude the situation of link to itself*/
	        if(algorithm_game.data[k][l] > 0)
	        {
	          GdkPoint p1,p2;
	          p1.x = i; p1.y = j;
	          p2.x = k; p2.y = l;
	          if(algorithm_can_link(p1,p2,NULL,NULL))
	          {
                    ui_replace_image(p1,p2); /*the window's redraw action is done in ui_replace_image function*/
                    /*switch the card image at p1 and p2,the image stand for hint status*/
                    if(gtk_check_menu_item_get_active(ui_menu_item.sound_effect))
					{
						pthread_t id;
						pthread_attr_t attr;
						int ret;
						pthread_attr_init(&attr);
						pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
						ret=pthread_create(&id,&attr,(void *) ui_play,"Hint.wav");
						if(ret!=0)
						{
							g_print (_("Create pthread error!\n"));
							exit (1);
						}
					}
			    	return; /*got a pair that can link,return immediately*/
	          }
	    }
	  }
	}
      }
    }
  }
}
/*
  according to the points input, get the link points between the two points
  and add these points in a single list.
*/
void 
ui_add_line(GdkPoint p1,GdkPoint p2, GSList **link_line)
{
	gint i;
	struct LinkPoint *tmp_point=NULL;
  
	if(p1.x == p2.x)
	{
		if (p1.y < p2.y)
			for(i = p1.y; i < p2.y; i++)
			{
				tmp_point = (struct LinkPoint *)g_malloc(sizeof(struct LinkPoint));
				tmp_point->x = p1.x;
				tmp_point->y = i;
				tmp_point->direction = 4;
				tmp_point->frame = 0;
				*link_line = g_slist_prepend(*link_line,tmp_point);
			}
		else
			for(i = p1.y; i > p2.y; i--)
			{
				tmp_point = (struct LinkPoint *)g_malloc(sizeof(struct LinkPoint));
				tmp_point->x = p1.x;
				tmp_point->y = i;
				tmp_point->direction = 3;
				tmp_point->frame = 0;
				*link_line = g_slist_prepend(*link_line,tmp_point);
			}
	}
	else  /*p1.y == p2.y*/
	{
		if (p1.x < p2.x)
			for(i=p1.x; i<p2.x; i++)
			{
				tmp_point = (struct LinkPoint *)g_malloc(sizeof(struct LinkPoint));
				tmp_point->x = i;
				tmp_point->y = p1.y;
				tmp_point->direction = 2;
				tmp_point->frame = 0;
				*link_line = g_slist_prepend(*link_line,tmp_point);
			}
		else
			for(i=p1.x; i>p2.x; i--)
			{
				tmp_point = (struct LinkPoint *)g_malloc(sizeof(struct LinkPoint));
				tmp_point->x = i;
				tmp_point->y = p1.y;
				tmp_point->direction = 1;
				tmp_point->frame = 0;
				*link_line = g_slist_prepend(*link_line,tmp_point);
			}
	}
}
/*
  dealing with the link line effect when delete cards in a newly created thread.
*/
void 
ui_draw_line(GSList *r_line)
{
/*  gint i;
  gint width,height;
  
  if(p1.x == p2.x)
  {
    if(p1.y < p2.y)
      for(i=p1.y; i<p2.y; i++)
      {
	width = gdk_pixbuf_get_width(ui_pixbuf.horizon);
	height = gdk_pixbuf_get_height(ui_pixbuf.horizon);
	gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.horizon,ui_double_pixmap,
                0,0,UI_FIXED_START_DRAW_LEFT+(i-algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1) + 20,
                UI_FIXED_START_DRAW_TOP + p1.x*(UI_BACK_HEIGHT-UI_BACK_BORDER_2),
		width,height,
                GDK_PIXBUF_ALPHA_BILEVEL,128,
                GDK_RGB_DITHER_NORMAL, 0, 0);
      }
    else
      for(i=p2.y; i<p1.y; i++)
      {
	width = gdk_pixbuf_get_width(ui_pixbuf.horizon);
	height = gdk_pixbuf_get_height(ui_pixbuf.horizon);
	gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.horizon,ui_double_pixmap,
                0,0,UI_FIXED_START_DRAW_LEFT + (i-algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1)+20,
                UI_FIXED_START_DRAW_TOP + p1.x*(UI_BACK_HEIGHT-UI_BACK_BORDER_2),
		width,height,
                GDK_PIXBUF_ALPHA_BILEVEL,128,
                GDK_RGB_DITHER_NORMAL, 0, 0);
      }
  }*/
//  else  /*p1.y == p2.y*/
/*  {
    if(p1.x < p2.x)
      for(i=p1.x; i<p2.x; i++)
      {
	width = gdk_pixbuf_get_width(ui_pixbuf.vertical);
	height = gdk_pixbuf_get_height(ui_pixbuf.vertical);
	gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.vertical,ui_double_pixmap,
                0,0,UI_FIXED_START_DRAW_LEFT + (p1.y-algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1),
                UI_FIXED_START_DRAW_TOP + i*(UI_BACK_HEIGHT - UI_BACK_BORDER_2) + 25,
		width,height,
                GDK_PIXBUF_ALPHA_BILEVEL,128,
                GDK_RGB_DITHER_NORMAL, 0, 0);
      }
    else
      for(i=p2.x; i<p1.x; i++)
      {
	width = gdk_pixbuf_get_width(ui_pixbuf.vertical);
	height = gdk_pixbuf_get_height(ui_pixbuf.vertical);
	gdk_pixbuf_render_to_drawable_alpha(ui_pixbuf.vertical,ui_double_pixmap,
                0,0,UI_FIXED_START_DRAW_LEFT + (p1.y-algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1),
                UI_FIXED_START_DRAW_TOP + i*(UI_BACK_HEIGHT-UI_BACK_BORDER_2) + 25,
		width,height,
                GDK_PIXBUF_ALPHA_BILEVEL,128,
                GDK_RGB_DITHER_NORMAL, 0, 0);
      }
  }*/
/* because on link will call ui_draw_line for 1 or 2 or 3 times,so the redraw 
   action should put after all lines are drawn.
   not put redraw action here.
*/
	int i=0,x=0,y=0,width=0,height=0;
	GdkPixbuf *tmp_pixbuf = NULL;
	struct LinkPoint *tmp_point = NULL;
	GdkRectangle update_rect;
	/* Reverse the points list.because we use prepend methord above
	   Whitch is more effective.
	*/
	GSList *link_line = g_slist_reverse (r_line);
    for(i=0;i<g_slist_length(link_line);i++)
    {
		tmp_point = (struct LinkPoint*)g_slist_nth_data(link_line,i);
		x = tmp_point->x;
		y = tmp_point->y;
		if (tmp_point->direction == 1 || tmp_point->direction == 2)
			tmp_pixbuf = ui_pixbuf.vertical;
		else
			tmp_pixbuf = ui_pixbuf.horizon;
		width = gdk_pixbuf_get_width(tmp_pixbuf);
		height = gdk_pixbuf_get_height(tmp_pixbuf);
		switch(tmp_point->direction)
		{
			case 1:
				gdk_pixbuf_render_to_drawable_alpha(tmp_pixbuf,ui_double_pixmap,
				0,0,UI_FIXED_START_DRAW_LEFT + 
				(tmp_point->y-algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1),
				UI_FIXED_START_DRAW_TOP + tmp_point->x*(UI_BACK_HEIGHT-UI_BACK_BORDER_2) - 25,
				width,height,
				GDK_PIXBUF_ALPHA_BILEVEL,128,
				GDK_RGB_DITHER_NORMAL, 0, 0);
				break;
			case 2:
				gdk_pixbuf_render_to_drawable_alpha(tmp_pixbuf,ui_double_pixmap,
				0,0,UI_FIXED_START_DRAW_LEFT + 
				(tmp_point->y-algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1),
				UI_FIXED_START_DRAW_TOP + tmp_point->x*(UI_BACK_HEIGHT - UI_BACK_BORDER_2) + 25,
				width,height,
				GDK_PIXBUF_ALPHA_BILEVEL,128,
				GDK_RGB_DITHER_NORMAL, 0, 0);
				break;
			case 3:
				gdk_pixbuf_render_to_drawable_alpha(tmp_pixbuf,ui_double_pixmap,
                0,0,UI_FIXED_START_DRAW_LEFT + 
				(tmp_point->y-algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1)-20,
                UI_FIXED_START_DRAW_TOP + tmp_point->x*(UI_BACK_HEIGHT-UI_BACK_BORDER_2),
				width,height,
                GDK_PIXBUF_ALPHA_BILEVEL,128,
                GDK_RGB_DITHER_NORMAL, 0, 0);
				break;
			case 4:
				gdk_pixbuf_render_to_drawable_alpha(tmp_pixbuf,ui_double_pixmap,
                0,0,UI_FIXED_START_DRAW_LEFT+
				(tmp_point->y-algorithm_game.difficulty)*(UI_BACK_WIDTH-UI_BACK_BORDER_1) + 20,
                UI_FIXED_START_DRAW_TOP + tmp_point->x*(UI_BACK_HEIGHT-UI_BACK_BORDER_2),
				width,height,
                GDK_PIXBUF_ALPHA_BILEVEL,128,
                GDK_RGB_DITHER_NORMAL, 0, 0);
				break;
		}
    }
    /*redraw window*/
    update_rect.x = 0;
    update_rect.y = 0;
    update_rect.width = ui_drawingarea->allocation.width;
    update_rect.height = ui_drawingarea->allocation.height;
    gtk_widget_draw (ui_drawingarea, &update_rect);
	/*free the single list and the data it refer.*/
	algorithm_free_with_data (link_line);
}
void 
ui_link(GdkPoint p1, GdkPoint p2)
{
	GSList *link_line = NULL;
	
	if(algorithm_can_direct_link(p1,p2))
	{
		ui_add_line(p1,p2,&link_line);
	}
	else
	{
		GdkPoint p3,p4;
		algorithm_can_link(p1,p2,&p3,&p4);
		ui_add_line(p1,p3,&link_line);
		if(p3.x != p4.x || p3.y != p4.y)ui_add_line(p3,p4,&link_line);
		ui_add_line(p4,p2,&link_line);
	}
	/* add thread here. */
	ui_draw_line (link_line);
}
/*
  Cheat
*/
void 
ui_game_cheat(GtkWidget *w,gpointer data)
{
  if(algorithm_game.status != ALGORITHM_GAME_STOP)
  {
    algorithm_game.life = 99;
    algorithm_game.hint = 99;
    time_remain = ui_get_time_limited();
    ui_refresh_top();
  }
}
/*Creat a background bitmap which has suitable size*/
static gint
configure_event (GtkWidget *widget, GdkEventConfigure *event)
{
  /* if the double pixmap exists, donot recreat, or the background
     will be black.	*/
  if (ui_double_pixmap)
	  return TRUE;
    //gdk_pixmap_unref(ui_double_pixmap);

  ui_double_pixmap = gdk_pixmap_new(widget->window,
                          widget->allocation.width,
                          widget->allocation.height,
                          -1);
  gdk_draw_rectangle (ui_double_pixmap,
                      widget->style->black_gc,
                      TRUE,
                      0, 0,
                      widget->allocation.width,
                      widget->allocation.height);

  return TRUE;
}
/*redraw screen base on the back ground bitmap*/
static gint
expose_event (GtkWidget *widget, GdkEventExpose *event)
{
  gdk_draw_pixmap(widget->window,
                  widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                  ui_double_pixmap,
                  event->area.x, event->area.y,
                  event->area.x, event->area.y,
                  event->area.width, event->area.height);
  return FALSE;
}

/*
  load ini setting file, and pak file.
  gchar **message: modify message,make it point to the error message.
  return value: gboolean, TRUE for success, FALSE for fail.
*/
gboolean
ui_load_ini_pak(gchar **message)
{
  struct passwd *user;
  int result;
  char *path = NULL;
  *message = NULL;
  gchar *return_str;
  GSList *radio_item_group=NULL;
  GtkWidget *menu,*menuitem;
  gint i;

  /* load ini file,if it do not exist, make a new one */
  user = getpwuid(getuid());
  /*user home directory: user->pw_dir*/
  path = g_strdup_printf ("%s/.llk_linux",user->pw_dir);
  result = mkdir(path,S_IRWXU);/*read write and execuable*/
  if(result == -1) 
  {
    if(errno != EEXIST)  /*Directory exists*/
    {
      *message = g_strdup (_("User Setting Save Error,fail to creat directory:$HOME/.llk_linux\n"));
      return FALSE;
    }
  }
  path = g_strdup_printf ("%s/UserSettings.ini",path);  /* path = $HOME/.llk_linux/UserSettings.ini */
  while(1)
  {
    if(g_file_test(path,G_FILE_TEST_EXISTS))
    {
      ui_ini = ini_file_open_file(path);
      if(ui_ini == NULL)
      {
        *message = g_strdup (_("Unable to read UserSettings.ini"));
        return FALSE;
      }
      else
      {
        gboolean tmp=FALSE;
        gchar *themename = NULL,*themenum = NULL;
        ini_file_read_boolean(ui_ini,"UISETTING","bgmusic",&tmp);
        if(tmp)gtk_check_menu_item_set_active(ui_menu_item.background_music,TRUE);
        else gtk_check_menu_item_set_active(ui_menu_item.background_music,FALSE);
        ini_file_read_boolean(ui_ini,"UISETTING","sound",&tmp);
        if(tmp)gtk_check_menu_item_set_active(ui_menu_item.sound_effect,TRUE);
        else gtk_check_menu_item_set_active(ui_menu_item.sound_effect,FALSE);
        ini_file_read_boolean(ui_ini,"UISETTING","bgpicture",&tmp);
        if(tmp)gtk_check_menu_item_set_active(ui_menu_item.background_picture,TRUE);
        else gtk_check_menu_item_set_active(ui_menu_item.background_picture,FALSE);
        /* read theme names and make menu items accordingly */
        menu = gtk_menu_new();
        gtk_menu_item_set_submenu( GTK_MENU_ITEM(ui_menu_item.themes),menu );
        /* read default themenum,and set according menu item's check status */
        if(!ini_file_read_string(ui_ini,"UISETTING", "themenum", &return_str))
        {
          *message = g_strdup (_("Failed to read \"[UISETTING]/themename\" key."));
          return FALSE;
        }
        themename = (gchar *)g_malloc(sizeof(gchar)*30);
        themenum  = (gchar *)g_malloc(sizeof(gchar)*10); /* "Theme10" string length = 8 */
        for(i=0;i<10;i++)
        {
          sprintf(themenum,"theme%d",i);
          ini_file_read_string(ui_ini,"THEMEFILE",themenum,&themename);
          if(!strcmp(themename,""))continue;
          menuitem = gtk_radio_menu_item_new_with_label (radio_item_group, themename);
          radio_item_group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
          gtk_menu_append(GTK_MENU(menu), menuitem);
          if(!strcmp(themenum,return_str)){
            gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
            ui_menu_item.current_theme = GTK_RADIO_MENU_ITEM(menuitem);
          }
          gtk_signal_connect(GTK_OBJECT (menuitem), "activate", GTK_SIGNAL_FUNC (radio_item_on_clicked), GINT_TO_POINTER(i));
          gtk_widget_show (menuitem);
        }
        g_free(themename);
        g_free(themenum);
        break;  /* exit while loop */
      }
    }
    else
    {
      ui_ini = ini_file_new();
      ini_file_write_boolean(ui_ini, "UISETTING",  "bgmusic",    FALSE          );
      ini_file_write_boolean(ui_ini, "UISETTING",  "sound"  ,    TRUE           );
      ini_file_write_boolean(ui_ini, "UISETTING",  "bgpicture",  TRUE           );
      ini_file_write_string (ui_ini, "UISETTING",  "themenum",   "theme0"    );
      /* Support at most 10 themes */
      ini_file_write_string (ui_ini, "THEMEFILE",  "theme0",     "Classical");
      ini_file_write_string (ui_ini, "THEMEFILE",  "theme1",     "QQ");
      ini_file_write_string (ui_ini, "THEMEFILE",  "theme2",     "Diamond");
      ini_file_write_string (ui_ini, "THEMEFILE",  "theme3",     "");
      ini_file_write_string (ui_ini, "THEMEFILE",  "theme4",     "");
      ini_file_write_string (ui_ini, "THEMEFILE",  "theme5",     "");
      ini_file_write_string (ui_ini, "THEMEFILE",  "theme6",     "");
      ini_file_write_string (ui_ini, "THEMEFILE",  "theme7",     "");
      ini_file_write_string (ui_ini, "THEMEFILE",  "theme8",     "");
      ini_file_write_string (ui_ini, "THEMEFILE",  "theme9",     "");

      ini_file_write_int    (ui_ini, "GAMERECORD", "difficulty", 1              );
    
      if(!ini_file_write_file(ui_ini,path))
      {
        *message = g_strdup (_("Unable to save $HOME/.llk_linux/UserSettings.ini"));
        return FALSE;
      }
      continue; /* continue,return to the start of while,to read ini file */
    }
  }
  g_free (path);
  /* load pak file */
  if(ini_file_read_string(ui_ini,"UISETTING", "themenum", &return_str))
  {
    gchar *tmpstr = return_str;  return_str = NULL;
    if( ! ini_file_read_string(ui_ini,"THEMEFILE",tmpstr, &return_str))
    {
      *message = g_strdup_printf (_("Failed to read \"[THEMEFILE]/%s\""),tmpstr);
      g_free(tmpstr);
      return FALSE;
    }
  }
  else
  {
    *message = g_strdup (_("Failed to read \"[UISETTING]/themename\" key."));
    return FALSE;
  }
  path = g_strdup_printf ("%s/%s/%s.pak",PACKAGE_DATA_DIR,PACKAGE,return_str);
  if( ! g_file_test(path,G_FILE_TEST_EXISTS))
  {
    *message = g_strdup_printf (_("The package file:LLK_DATA_PATH/pak/%s does not exists."),return_str);
    g_free(return_str);
    return FALSE;
  }
  g_free(return_str);
  if( ! LoadPAKHFT(path))
  {
    *message = g_strdup (_("LoadPAKHFT error."));
    return FALSE;
  }
  g_free (path);
  pak_info.back_num = GetFileNum("back","jpg");
  pak_info.sound_num = GetFileNum("sound","wav");
  pak_info.music_num = GetFileNum("music","mid");

  if( !ExtractSingleFile("cardimages.png") ||  !ExtractSingleFile("cardbacks.png") ||  !ExtractSingleFile("horizon.png")
      ||  !ExtractSingleFile("vertical.png") ||  !ExtractSingleFile("pause.jpg") ||  !ExtractSingleFile("logo.png") 
      ||  !ExtractSingleFile("mainback.jpg") )
  {
    *message = g_strdup (_("Failed to extract necessary jpg/png files."));
    return FALSE;
  }
  ui_pixbuf.cardimages = gdk_pixbuf_new_from_file("/tmp/llk_cardimages.png",NULL);
  ui_pixbuf.cardbacks  = gdk_pixbuf_new_from_file("/tmp/llk_cardbacks.png",NULL);
  ui_pixbuf.vertical   = gdk_pixbuf_new_from_file("/tmp/llk_vertical.png",NULL);
  ui_pixbuf.horizon    = gdk_pixbuf_new_from_file("/tmp/llk_horizon.png",NULL);
  ui_pixbuf.logo       = gdk_pixbuf_new_from_file("/tmp/llk_logo.png",NULL);
  ui_pixbuf.pause      = gdk_pixbuf_new_from_file("/tmp/llk_pause.jpg",NULL);
  ui_pixbuf.mainback   = gdk_pixbuf_new_from_file("/tmp/llk_mainback.jpg",NULL);
  ui_pixbuf.cardback_choice = g_rand_int_range(ui_rand,0,6); /*begin to end-1*/
  if(pak_info.back_num > 0){
    ui_pixbuf.randomback_choice = g_rand_int_range(ui_rand,1,pak_info.back_num+1);
    /* Extract the bg picture and read it to ui_pixbuf.randomback */
    gchar *bgfilename = NULL;
    bgfilename = g_strdup_printf ("back%d.jpg",ui_pixbuf.randomback_choice-1);
    if(!ExtractSingleFile(bgfilename)){g_print(_("Failed to extract file:%s.\n"),bgfilename);}
	g_free (bgfilename);
    bgfilename = g_strdup_printf ("/tmp/llk_back%d.jpg",ui_pixbuf.randomback_choice-1);
    if(ui_pixbuf.randomback)gdk_pixbuf_unref(ui_pixbuf.randomback); /* Free old randomback pixbuf */
    ui_pixbuf.randomback = gdk_pixbuf_new_from_file(bgfilename,NULL);
    remove(bgfilename);
	g_free (bgfilename);
    if(ui_pixbuf.randomback == NULL){ui_pixbuf.randomback = ui_pixbuf.mainback;g_print(_("randomback=NULL,Error occored.\n"));}
  }
  else{
    ui_pixbuf.randomback = NULL;
    ui_pixbuf.randomback_choice = 0;
  }
  remove("/tmp/llk_cardimages.png");
  remove("/tmp/llk_cardbacks.png");
  remove("/tmp/llk_vertical.png");
  remove("/tmp/llk_horizon.png");
  remove("/tmp/llk_logo.png");
  remove("/tmp/llk_pause.jpg");
  remove("/tmp/llk_mainback.jpg");
  if(  !ui_pixbuf.cardimages || !ui_pixbuf.cardbacks || !ui_pixbuf.vertical || !ui_pixbuf.horizon || !ui_pixbuf.logo
    || !ui_pixbuf.pause || !ui_pixbuf.mainback )
  {
    *message = g_strdup (_("Convert jpg/png files into ui_pixbuf error."));
    return FALSE;
  }
  return TRUE;
}

void ui_use_m_s_bg( GtkWidget *w,gpointer   data )
{
  switch(GPOINTER_TO_INT(data))
  {
    case 0:
      ini_file_write_boolean(ui_ini,"UISETTING","bgmusic",gtk_check_menu_item_get_active(ui_menu_item.background_music));
      break;
    case 1:
      ini_file_write_boolean(ui_ini,"UISETTING","sound",gtk_check_menu_item_get_active(ui_menu_item.sound_effect));
      break;
    case 2:
      ini_file_write_boolean(ui_ini,"UISETTING","bgpicture",gtk_check_menu_item_get_active(ui_menu_item.background_picture));
      /* redraw all images */
      if(algorithm_game.status == ALGORITHM_GAME_RUN)ui_redraw_images();
      break;
  }    
  if(!ini_file_write_file(ui_ini,ui_ini->filename))
  {
    /* g_print("Ini file save error!\n"); */
  }
}

/*
  empty call back funtion, use for testing
*/
void
radio_item_on_clicked( GtkWidget *w, gpointer   data )
{
  gchar *themenum = NULL;
  gchar *return_str;
  gchar *path = NULL;
  gboolean success=TRUE;
  static gboolean called_from_menu = TRUE;

  if(!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(w)))return;
  if(called_from_menu == FALSE)return;
  themenum = g_strdup_printf ("theme%d",GPOINTER_TO_INT(data));
  
  /* load pak file */
  if( ! ini_file_read_string(ui_ini,"THEMEFILE",themenum, &return_str))
  {
    g_print(_("Failed to read \"[THEMEFILE]/%s\"\n"),themenum);
    success = FALSE;
  }
  else
  {
    path = g_strdup_printf ("%s/%s/%s.pak",PACKAGE_DATA_DIR,PACKAGE,return_str);
    g_free(return_str);
    if( ! g_file_test(path,G_FILE_TEST_EXISTS))
    {
      g_print(_("The package file:LLK_DATA_PATH/%s does not exists.\n"),themenum);
      success = FALSE;
    }
    else
    {
      if( ! LoadPAKHFT(path))
      {
        g_print(_("LoadPAKHFT error.\n"));
        success = FALSE;
      }
      else
      {
        pak_info.back_num = GetFileNum("back","jpg");
        pak_info.sound_num = GetFileNum("sound","wav");
        pak_info.music_num = GetFileNum("music","mid");

        if( !ExtractSingleFile("cardimages.png") ||  !ExtractSingleFile("cardbacks.png") ||  !ExtractSingleFile("horizon.png")
            ||  !ExtractSingleFile("vertical.png") ||  !ExtractSingleFile("pause.jpg") ||  !ExtractSingleFile("logo.png") 
            ||  !ExtractSingleFile("mainback.jpg") )
        {
          g_print(_("Failed to extract necessary jpg/png files.\n"));
          success = FALSE;
        }
        else
        {
          gdk_pixbuf_unref(ui_pixbuf.cardimages);
          gdk_pixbuf_unref(ui_pixbuf.cardbacks);
          gdk_pixbuf_unref(ui_pixbuf.vertical);
          gdk_pixbuf_unref(ui_pixbuf.horizon);
          gdk_pixbuf_unref(ui_pixbuf.logo);
          gdk_pixbuf_unref(ui_pixbuf.pause);
          gdk_pixbuf_unref(ui_pixbuf.mainback);
          ui_pixbuf.cardimages = gdk_pixbuf_new_from_file("/tmp/llk_cardimages.png",NULL);
          ui_pixbuf.cardbacks  = gdk_pixbuf_new_from_file("/tmp/llk_cardbacks.png",NULL);
          ui_pixbuf.vertical   = gdk_pixbuf_new_from_file("/tmp/llk_vertical.png",NULL);
          ui_pixbuf.horizon    = gdk_pixbuf_new_from_file("/tmp/llk_horizon.png",NULL);
          ui_pixbuf.logo       = gdk_pixbuf_new_from_file("/tmp/llk_logo.png",NULL);
          ui_pixbuf.pause      = gdk_pixbuf_new_from_file("/tmp/llk_pause.jpg",NULL);
          ui_pixbuf.mainback   = gdk_pixbuf_new_from_file("/tmp/llk_mainback.jpg",NULL);
          /* ui_pixbuf.cardback_choice = g_rand_int_range(ui_rand,0,6);*//*Do not change card back choice when change theme*/
          if(pak_info.back_num > 0){
              ui_pixbuf.randomback_choice = g_rand_int_range(ui_rand,1,pak_info.back_num+1);
              /* Extract the bg picture and read it to ui_pixbuf.randomback */
              gchar *bgfilename = NULL;
              bgfilename = g_strdup_printf ("back%d.jpg",ui_pixbuf.randomback_choice-1);
              if(!ExtractSingleFile(bgfilename)){g_print(_("Failed to extract file:%s.\n"),bgfilename);}
              g_free (bgfilename);
			  bgfilename = g_strdup_printf ("/tmp/llk_back%d.jpg",ui_pixbuf.randomback_choice-1);
              if(ui_pixbuf.randomback)gdk_pixbuf_unref(ui_pixbuf.randomback); /* Free old randomback pixbuf */
              ui_pixbuf.randomback = gdk_pixbuf_new_from_file(bgfilename,NULL);
              remove(bgfilename);
			  g_free (bgfilename);
              if(ui_pixbuf.randomback == NULL){ui_pixbuf.randomback = ui_pixbuf.mainback;g_print(_("randomback=NULL,Error occored.\n"));}
          }
          else{
            ui_pixbuf.randomback = NULL;
            ui_pixbuf.randomback_choice = 0; 
          }
          remove("/tmp/llk_cardimages.png");
          remove("/tmp/llk_cardbacks.png");
          remove("/tmp/llk_vertical.png");
          remove("/tmp/llk_horizon.png");
          remove("/tmp/llk_logo.png");
          remove("/tmp/llk_pause.jpg");
          remove("/tmp/llk_mainback.jpg");
          if(  !ui_pixbuf.cardimages || !ui_pixbuf.cardbacks || !ui_pixbuf.vertical || !ui_pixbuf.horizon || !ui_pixbuf.logo
            || !ui_pixbuf.pause || !ui_pixbuf.mainback )
          {
            g_print(_("Convert jpg/png files into ui_pixbuf error.\n"));
            success = FALSE;
          }
        }
      }
    }
  }
  if(success)
  {
    ini_file_write_string(ui_ini,"UISETTING","themenum",themenum);
    if(!ini_file_write_file(ui_ini,ui_ini->filename)){/* g_print("Ini file save error!\n"); */}
    ui_menu_item.current_theme = GTK_RADIO_MENU_ITEM(w);
    /* redraw all images */
    if(algorithm_game.status == ALGORITHM_GAME_RUN)ui_redraw_images();
  }
  else
  {
    /* ignore the error of convert png file,when other errors occored,because we have not change anything,
       so just reset the radio menu item's active status */
    called_from_menu = FALSE;
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(ui_menu_item.current_theme),TRUE);
    called_from_menu = TRUE;
  }
  g_free (path);
  g_free (themenum);
}

gboolean 
ui_save_game_data(void)
{
  FILE *fp;
  struct passwd *user;
  gchar *path = NULL;
  /* load ini file,if it do not exist, make a new one */
  user = getpwuid(getuid());
  /*user home directory: user->pw_dir*/
  path = g_strdup_printf ("%s/.llk_linux/save.dat",user->pw_dir);
  fp = fopen(path,"wb");
  g_free (path);
  if(fp)
  {
    fwrite(&algorithm_game,sizeof(struct AlgorithmGame),1,fp);
    fwrite(&time_remain,sizeof(gint),1,fp);
    fclose(fp);
    return TRUE;
  }
  else
  {
    g_print(_("Open save.dat file error.\n"));
    return FALSE;
  }
}
gboolean 
ui_read_game_data(void)
{
  FILE *fp;
  struct passwd *user;
  gchar *path = NULL;
  /* load ini file,if it do not exist, make a new one */
  user = getpwuid(getuid());
  /*user home directory: user->pw_dir*/
  path = g_strdup_printf("%s/.llk_linux/save.dat",user->pw_dir);
  fp = fopen(path,"rb");
  g_free (path);
  if(fp)
  {
    fread(&algorithm_game,sizeof(struct AlgorithmGame),1,fp);
    fread(&time_remain,sizeof(gint),1,fp);
    fclose(fp);
    return TRUE;
  }
  else
  {
    g_print(_("Open save.dat file error.\n"));
    return FALSE;
  }
}
void ui_input_string(gchar *str1,gchar *str2,gint max_length)
{
  GtkWidget *dialog;
  GtkWidget *label,*entry_name,*entry_nick;
  GtkWidget *hbox,*button;
  gint result;
  g_assert(max_length > 0);

  dialog = gtk_dialog_new();
  gtk_window_set_title(GTK_WINDOW(dialog),_("Input your name and nick"));
  gtk_container_border_width(GTK_CONTAINER(dialog), 5);
      hbox = gtk_hbox_new(FALSE,10);  
      gtk_box_pack_start (GTK_BOX (GTK_DIALOG(dialog)->vbox),hbox,FALSE,TRUE,5);
        label = gtk_label_new(_(" Name "));
        gtk_widget_set_size_request(label,100,30);
        gtk_box_pack_start (GTK_BOX(hbox),label,FALSE,TRUE,5);
        gtk_widget_show(label);
        entry_name = gtk_entry_new_with_max_length(max_length);
        gtk_box_pack_start (GTK_BOX(hbox),entry_name,FALSE,TRUE,5);
        gtk_widget_show(entry_name);
      gtk_widget_show(hbox);
      hbox = gtk_hbox_new(FALSE,10);  
      gtk_box_pack_start (GTK_BOX (GTK_DIALOG(dialog)->vbox),hbox,FALSE,TRUE,5);
        label = gtk_label_new(_(" Nick "));
        gtk_widget_set_size_request(label,100,30);
        gtk_box_pack_start (GTK_BOX(hbox),label,FALSE,TRUE,5);
        gtk_widget_show(label);
        entry_nick = gtk_entry_new_with_max_length(max_length);
        gtk_box_pack_start (GTK_BOX(hbox),entry_nick,FALSE,TRUE,5);
        gtk_widget_show(entry_nick);
      gtk_widget_show(hbox);
  /*Button area*/
  button = gtk_dialog_add_button(GTK_DIALOG(dialog),_("OK"),GTK_RESPONSE_ACCEPT);
  gtk_widget_show(button);
  button = gtk_dialog_add_button(GTK_DIALOG(dialog),_("Cancel"),GTK_RESPONSE_CANCEL);
  gtk_widget_show(button);
  result = gtk_dialog_run (GTK_DIALOG (dialog));
  switch (result)
  {
      case GTK_RESPONSE_ACCEPT:
         sprintf(str1,"%s",gtk_entry_get_text(GTK_ENTRY(entry_name)));
         sprintf(str2,"%s",gtk_entry_get_text(GTK_ENTRY(entry_nick)));
         break;
      default:
         sprintf(str1,"%s","");
         sprintf(str2,"%s","");
         break;
  }
  gtk_widget_destroy (dialog);
}

void ui_record_score(gboolean view)
{
  struct ScoreItem{
    gchar score[30];
    gchar name[51];
    gchar nick[51];
    gchar difficulty[10];
    gchar level[3];
    gchar time[30];
    struct ScoreItem *prev;
    struct ScoreItem *next;
  };
  FILE *fp;
  struct passwd *user;
  gchar *path = NULL;
  struct ScoreItem *score_list=NULL,*score_item_end=NULL,*score_item_tmp;
  gint item_num=0;
  /* load ini file,if it do not exist, make a new one */
  user = getpwuid(getuid());
  /*user home directory: user->pw_dir*/
  path = g_strdup_printf ("%s/.llk_linux/score.dat",user->pw_dir);
  fp = fopen(path,"rb");
  if(fp != NULL)
  {
    while(1)
    {
      score_item_tmp = (struct ScoreItem *)malloc(sizeof(struct ScoreItem));
      fread(score_item_tmp,sizeof(struct ScoreItem),1,fp);
      score_item_tmp->next = NULL;
      score_item_tmp->prev = NULL;
      if(feof(fp)) {g_free(score_item_tmp);break;}
      if(score_item_end)
      {
        score_item_end->next = score_item_tmp;
        score_item_tmp->prev = score_item_end;
        score_item_end = score_item_tmp;
      }
      else
      {
        score_list = score_item_tmp;
        score_item_end = score_list;
      }
      item_num++;
    }
    fclose(fp);
  }
  else
  {
    g_print(_("Open file error.\n"));
  }
  if(!view) /* If not just view the score,then this function must be called by ui_game_over,so add the current player's score
               into the list,and then write to file if the list is modified,and at last,show the score list on a new window */
  {
    gint insert_pos=1;
    for(score_item_tmp = score_list;score_item_tmp!=NULL;score_item_tmp=score_item_tmp->next)
    {
      if(algorithm_game.score > atoi(score_item_tmp->score))break;
      insert_pos++; 
    }
    if(insert_pos > 10)
    {insert_pos=0;score_item_tmp=NULL;}
    else
    {
      if(insert_pos == 1)
      {
        if(score_list == NULL)
        {
          score_list = (struct ScoreItem *)g_malloc(sizeof(struct ScoreItem));
          score_list->prev = NULL;
          score_list->next = NULL;
          score_item_end = score_list;
          score_item_tmp = score_list;
        }
        else
        {
          score_item_tmp = (struct ScoreItem *)g_malloc(sizeof(struct ScoreItem));
          score_item_tmp->prev = NULL;
          score_item_tmp->next = score_list;
          score_list->prev = score_item_tmp;
          score_list = score_item_tmp;
        }
      }
      else
      {
        score_item_tmp = score_list;
        while(TRUE)
        {
          if(insert_pos == 2)
          {
            struct ScoreItem *tmp=(struct ScoreItem *)g_malloc(sizeof(struct ScoreItem));
            tmp->next = score_item_tmp->next;
            tmp->prev = score_item_tmp;
            score_item_tmp->next = tmp;
            item_num++;
            break;
          }
          else
          {
            score_item_tmp = score_item_tmp->next;
            insert_pos--;
          }
        }
        score_item_tmp = score_item_tmp->next;
      }
    }
    if(item_num==11)
    {
      score_item_end = score_item_end->prev;
      g_free(score_item_end->next);
      score_item_end->next = NULL;
      item_num--;
    }
    sprintf(score_item_tmp->score,"%d",algorithm_game.score);
    switch(algorithm_game.difficulty)
    {
      case 0:sprintf(score_item_tmp->difficulty,_("Easy"));
             break;
      case 1:sprintf(score_item_tmp->difficulty,_("Normal"));
             break;
      case 2:sprintf(score_item_tmp->difficulty,_("Hard"));
             break;
      default:sprintf(score_item_tmp->difficulty,_("Unknown"));
             break;
    }
    sprintf(score_item_tmp->level,"%d",algorithm_game.level);
    time_t t;
    time(&t);
    sprintf(score_item_tmp->time,"%s",asctime(gmtime(&t)));
    ui_input_string(score_item_tmp->name,score_item_tmp->nick,50);
    if(insert_pos != 0)  /* score_list has been changed,so save it to file */
    {
      /* Write it to file */
      fp = fopen(path,"wb");
      if(fp!=NULL)
      {
        for(score_item_tmp=score_list;score_item_tmp!=NULL;score_item_tmp=score_item_tmp->next)
        {
          fwrite(score_item_tmp,sizeof(struct ScoreItem),1,fp);
        }
        fclose(fp);
      }
      else
      {
        g_print(_("Open score.dat error.\n"));
      }
    }
    else
    {
	  g_free (path);
      return;/* If player's score is not within 10,no record it,and no show the score window. */
    }
  }
  g_free (path);
  /* Create a new window to show scores. */
  GtkWidget *dialog,*tree_view,*button;
  GtkCellRenderer *renderer;
  GtkListStore  *store;
  GtkTreeIter    iter;
  dialog = gtk_dialog_new();
  gtk_window_set_title(GTK_WINDOW(dialog),_("Top 10 Heros"));
  gtk_container_border_width(GTK_CONTAINER(dialog),5);
  /* Create treeview widget and set data into it */
  tree_view = gtk_tree_view_new ();
  /* --- Column #1 --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (tree_view),-1,_("Position"),renderer,"text", 0,NULL);
  /* --- Column #2 --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (tree_view),-1,_("Score"),renderer,"text", 1,NULL);
  /* --- Column #3 --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (tree_view),-1,_("Name"),renderer,"text", 2,NULL);
  /* --- Column #4 --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (tree_view),-1,_("Nick name"),renderer,"text", 3,NULL);
  /* --- Column #5 --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (tree_view),-1,_("Difficulty"),renderer,"text", 4,NULL);
  /* --- Column #6 --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (tree_view),-1,_("Level"),renderer,"text", 5,NULL);
  /* --- Column #7 --- */
  renderer = gtk_cell_renderer_text_new ();
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (tree_view),-1,_("Data&Time"),renderer,"text", 6,NULL);
  /*-------------------*/
  store = gtk_list_store_new (7,G_TYPE_UINT,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
  score_item_tmp=score_list;
  for(item_num=0;item_num<10;item_num++)
  {
    if(score_item_tmp)
    {
      /* Append a row and fill in some data */
      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter,0,item_num+1, 1,score_item_tmp->score,
                2, score_item_tmp->name, 3, score_item_tmp->nick,
                4,score_item_tmp->difficulty,5,score_item_tmp->level,
                6,score_item_tmp->time, -1);
      score_item_tmp=score_item_tmp->next;
    }
    else
    {
      /* Append a row and fill in some data */
      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter,
                0,item_num+1, 1, "",
                2, ""       , 3, "",
                4, ""       , 5, "",
                6, ""       , -1);
    }
  }
  gtk_tree_view_set_model (GTK_TREE_VIEW (tree_view), GTK_TREE_MODEL(store));
  /* The tree view has acquired its own reference to the
   * model, so we can drop ours. That way the model will
   * be freed automatically when the tree view is destroyed */
  g_object_unref (GTK_TREE_MODEL(store));
    /* Free memory */
  while(score_list)
  {
    score_item_tmp = score_list->next;
    g_free(score_list);
    score_list = score_item_tmp;
  }
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),tree_view,FALSE,TRUE,5);
  /* Create button */
  button = gtk_button_new_with_label(_(" Close "));
  gtk_signal_connect_object(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy), GTK_OBJECT(dialog));
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), button, FALSE, FALSE, 0);
  gtk_widget_show_all(dialog);
}

void ui_view_score( GtkWidget *w,gpointer data)
{
  ui_record_score(TRUE);
}
void ui_theme_editor( GtkWidget *w,gpointer   data )
{
  create_pak_dialog();
}
/* tray popup menu call back function */
static void
tray_popup_activate_action (GtkAction * action)
{
	g_message ("Action \"%s\" activated", gtk_action_get_name (action));
}

/*
  main function,creat window widget,enter main message loop.
  ATTENTION,after creating drawingarea,assign the value of ui_drawingarea.
*/
int 
main (int argc , char* argv[])
{
	GtkWidget *window;
	GtkWidget *main_vbox,*vbox,*hbox;
	GtkWidget *menubar;
	gchar     *message;
	LlkTray *tray;
	GError *tray_error = NULL;
static GtkActionEntry tray_popup_entries[] = {
/*	{"Restore", GTK_STOCK_PREFERENCES,
	 N_("_Restore"), NULL,
	 N_("Restore"),
	 G_CALLBACK (tray_popup_activate_action)},	*/
	{"Help", GTK_STOCK_HELP,
	 N_("_Help"), NULL,
	 N_("Help"),
	 G_CALLBACK (ui_rule)},	
	{"Quit", GTK_STOCK_QUIT,	/* name, stock id */
	 N_("_Quit"), NULL,	/* label, accelerator */
	 N_("Quit"),		/* tooltip */
	 G_CALLBACK (gtk_main_quit)},
	{"About", GTK_STOCK_ABOUT,	/* name, stock id */
	 N_( "_About"), NULL,	/* label, accelerator */
	 N_("About"),		/* tooltip */
	 G_CALLBACK (ui_about)},
};

static const gchar *tray_popup_ui_info =
	"<ui>"
	"  <popup name='PopupMenu'>"
/*	"    <menuitem action='Restore'/>" */
	"    <menuitem action='Help'/>"
	"    <menuitem action='About'/>"
	"    <separator/>"
	"    <menuitem action='Quit'/>"
	"  </popup>"
	"</ui>";
	
#ifdef ENABLE_NLS
	bindtextdomain (PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset(PACKAGE, "UTF-8");
	textdomain (PACKAGE);
#endif	
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window),"delete-event",
					G_CALLBACK(gtk_main_quit),NULL);
    
	message=g_strdup_printf("%s%s%s",_("Lian Lian Kan "),VERSION,_(" by Alpher"));
	gtk_window_set_title(GTK_WINDOW(window),message);
	g_free(message);
	
	//gtk_window_set_default_size(GTK_WINDOW(window),770+4,600+30);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	//gtk_window_set_policy(GTK_WINDOW(window),TRUE,FALSE,FALSE);
	gtk_window_set_resizable (GTK_WINDOW(window),FALSE);
	/* set tray icon */
	tray = g_new0 (LlkTray, 1);
	tray->window_main = window;
	tray->show_hide_call_back = ui_hide_window;
	llk_create_tray (tray);
	/* create popup menu ui */
	tray->actions = gtk_action_group_new ("Actions");
	gtk_action_group_set_translation_domain (tray->actions,GETTEXT_PACKAGE);
	gtk_action_group_add_actions (tray->actions, tray_popup_entries, 
		G_N_ELEMENTS (tray_popup_entries), NULL);
	tray->ui = gtk_ui_manager_new ();
	gtk_ui_manager_insert_action_group (tray->ui, tray->actions, 0);
	gtk_window_add_accel_group (GTK_WINDOW (window), 
		gtk_ui_manager_get_accel_group (tray->ui));
	if (!gtk_ui_manager_add_ui_from_string (tray->ui, tray_popup_ui_info, -1, &tray_error))
	{
		g_message ("building menus failed:%s", tray_error->message);
		g_error_free (tray_error);
	}
	tray->menus = gtk_ui_manager_get_widget (tray->ui, "/PopupMenu");
	
	main_vbox = gtk_vbox_new(FALSE,1);
	gtk_container_set_border_width(GTK_CONTAINER(main_vbox),1);
	gtk_container_add(GTK_CONTAINER(window),main_vbox);
	gtk_widget_show(main_vbox);

	/*deal with main menu*/
	vbox = gtk_vbox_new(FALSE,1);
	gtk_container_set_border_width(GTK_CONTAINER(vbox),1);
	gtk_box_pack_start(GTK_BOX(main_vbox),vbox,FALSE,TRUE,0);
	gtk_widget_show(vbox);
	get_main_menu(window,&menubar);
	/*the first parameter FALSE,indicate the the main menu will no fullfill the main_vbox,
	  the last parameter 0,is the spacing value of the main menu and the top of main_vbox*/
	gtk_box_pack_start(GTK_BOX(vbox),menubar,FALSE,TRUE,0);
	gtk_widget_show(menubar);
	/*connect /functions/hide menuitem's event to hide window process*/
	g_signal_connect(G_OBJECT(
		g_list_nth_data (GTK_MENU (gtk_menu_item_get_submenu (GTK_MENU_ITEM (
			g_list_nth_data (GTK_MENU_BAR(menubar)->menu_shell.children,1))))->menu_shell.children
			, 4)
		),"activate",G_CALLBACK(ui_hide_window),(gpointer)tray);

	/*deal with the top area.top of the game area*/
	hbox = gtk_hbox_new(FALSE,1);
	gtk_box_pack_start(GTK_BOX(main_vbox),hbox,FALSE,TRUE,0);
	gtk_widget_show(hbox);
	ui_top.label_difficulty = gtk_label_new_with_mnemonic(_("Diff:"));
	gtk_widget_set_size_request(ui_top.label_difficulty,75,20);
	gtk_label_set_justify(GTK_LABEL(ui_top.label_difficulty),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(hbox),ui_top.label_difficulty,FALSE,FALSE,0);
	gtk_widget_show(ui_top.label_difficulty);
	ui_top.label_level = gtk_label_new_with_mnemonic(_("Lev:"));
	gtk_widget_set_size_request(ui_top.label_level,50,20);
	gtk_label_set_justify(GTK_LABEL(ui_top.label_level),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(hbox),ui_top.label_level,FALSE,FALSE,0);
	gtk_widget_show(ui_top.label_level);
	ui_top.label_life = gtk_label_new_with_mnemonic(_("Life:"));
	gtk_widget_set_size_request(ui_top.label_life,50,20);
	gtk_label_set_justify(GTK_LABEL(ui_top.label_life),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(hbox),ui_top.label_life,FALSE,FALSE,0);
	gtk_widget_show(ui_top.label_life);
	ui_top.label_hint = gtk_label_new_with_mnemonic(_("Hint:"));
	gtk_widget_set_size_request(ui_top.label_hint,50,20);
	gtk_label_set_justify(GTK_LABEL(ui_top.label_hint),GTK_JUSTIFY_LEFT);
	gtk_box_pack_start(GTK_BOX(hbox),ui_top.label_hint,FALSE,FALSE,0);
	gtk_widget_show(ui_top.label_hint);
	ui_top.label_change_type = gtk_label_new_with_mnemonic(_("Change Type:"));
	gtk_widget_set_size_request(ui_top.label_change_type,150,20);
	gtk_label_set_justify(GTK_LABEL(ui_top.label_change_type),GTK_JUSTIFY_CENTER);
	gtk_box_pack_start(GTK_BOX(hbox),ui_top.label_change_type,FALSE,FALSE,0);
	gtk_widget_show(ui_top.label_change_type);
	ui_top.progress_bar = gtk_progress_bar_new();
	gtk_widget_set_size_request(ui_top.progress_bar,295,20);
	gtk_box_pack_start(GTK_BOX(hbox),ui_top.progress_bar,FALSE,FALSE,0);
	gtk_widget_show(ui_top.progress_bar);
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(ui_top.progress_bar),0);
	ui_top.label_score = gtk_label_new_with_mnemonic("0");
	gtk_widget_set_size_request(ui_top.label_score,50,20);
	gtk_label_set_justify(GTK_LABEL(ui_top.label_score),GTK_JUSTIFY_LEFT);
	gtk_box_pack_end(GTK_BOX(hbox),ui_top.label_score,FALSE,FALSE,0);
	gtk_widget_show(ui_top.label_score);
	
	/*deal with game area*/
	vbox = gtk_vbox_new(FALSE,1);
	gtk_container_set_border_width(GTK_CONTAINER(vbox),0);
	gtk_box_pack_start(GTK_BOX(main_vbox),vbox,FALSE,TRUE,0);
	gtk_widget_show(vbox);
	ui_drawingarea = gtk_drawing_area_new();
	gtk_widget_set_size_request(ui_drawingarea,720,460);
	gtk_box_pack_start( GTK_BOX(main_vbox),ui_drawingarea,FALSE,TRUE,0);
	gtk_signal_connect (GTK_OBJECT (ui_drawingarea), "expose_event",
                      (GtkSignalFunc) expose_event, NULL);
	gtk_signal_connect (GTK_OBJECT(ui_drawingarea),"configure_event",
                      (GtkSignalFunc) configure_event, NULL);
	gtk_signal_connect (GTK_OBJECT (ui_drawingarea), "button_press_event",
                      (GtkSignalFunc) ui_drawingarea_clicked, NULL);

	gtk_widget_set_events (ui_drawingarea, GDK_EXPOSURE_MASK
                         | GDK_LEAVE_NOTIFY_MASK
                         | GDK_BUTTON_PRESS_MASK
                         | GDK_POINTER_MOTION_HINT_MASK);
	/*draw back ground picture,undo*/
	gtk_widget_show(ui_drawingarea);
	gtk_widget_show(window); 
    /* Generate GRand */
    ui_rand = g_rand_new();
	/* load ini settings and pak file */
	if(!ui_load_ini_pak(&message))
	{
		GtkWidget *dialog;
		dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
				GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,message);
		gtk_dialog_run(GTK_DIALOG(dialog));
		g_free(message);
		gtk_widget_destroy(dialog);
		return FALSE;
	}
    /* Set winodw icon */
	gtk_window_set_icon(GTK_WINDOW(window),ui_pixbuf.logo);
	ui_game_init(); /*init,ready to game start*/
	esd_fd = 0; /*esd_open_sound(NULL);*/
	gtk_main();  /*enter main message loop*/
	// if(esd_fd > 0)esd_close(esd_fd);
        /* If player quit game while playing, call save_game_data */
        if(algorithm_game.status != ALGORITHM_GAME_STOP && !ui_save_game_data()){g_print(_("Save game data to file error.\n"));}
	return FALSE;
}
