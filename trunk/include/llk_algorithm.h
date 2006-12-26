/***************************************************************************
 *            llk_algorithm.h
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
 
#ifndef __LLK_ALGORITHM_H
#define __LLK_ALGORITHM_H
#include <gtk/gtk.h>
#include <time.h>
#include <stdlib.h>
#include <glib/gi18n.h>
#define ALGORITHM_GAME_STOP  1
#define ALGORITHM_GAME_RUN   2
#define ALGORITHM_GAME_PAUSE 3

struct AlgorithmGame{
	gint difficulty;
	gint level;
	gint life;
	gint hint;
	gint score;
	gint row,col;
	gint status; /*Game status*/
	gint data[9][16]; /*0:no pic,1: pic1,*/
};

struct AlgorithmGame algorithm_game;
gboolean algorithm_game_init(void);
gboolean algorithm_game_begin(gpointer data);
gboolean algorithm_can_direct_link(GdkPoint p1, GdkPoint p2); 
gboolean algorithm_can_link(GdkPoint p1, GdkPoint p2, GdkPoint *pp3, GdkPoint *pp4); 
void     algorithm_link(GdkPoint p1,GdkPoint p2);
GSList * algorithm_get_points(GdkPoint p);
void     algorithm_free_with_data(GSList *list);
gint     algorithm_game_no_solution(void);
void     algorithm_game_shuffle(void);
void     algorithm_game_change(GdkPoint p1, GdkPoint p2);
gboolean algorithm_game_net_level(void);
void     algorithm_init_data(void);
void     algorithm_data_change_0(GdkPoint p1, GdkPoint p2);
void     algorithm_data_change_1(GdkPoint p1, GdkPoint p2);
void     algorithm_data_change_2(GdkPoint p1, GdkPoint p2);
void     algorithm_data_change_3(GdkPoint p1, GdkPoint p2);
void     algorithm_data_change_4(GdkPoint p1, GdkPoint p2);
void     algorithm_data_change_5(GdkPoint p1, GdkPoint p2);
void     algorithm_data_change_6(GdkPoint p1, GdkPoint p2);
void     algorithm_data_change_7(GdkPoint p1, GdkPoint p2);
void     algorithm_data_change_8(GdkPoint p1, GdkPoint p2);
void     algorithm_data_change_9(GdkPoint p1, GdkPoint p2);
void     algorithm_data_change_10(GdkPoint p1, GdkPoint p2);

#endif
