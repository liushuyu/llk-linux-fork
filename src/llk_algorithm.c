/***************************************************************************
 *            llk_algorithm.c
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

#include <llk_algorithm.h>

struct AlgorithmGame algorithm_game;

gboolean algorithm_game_init(void) {
  gint i, j;
  algorithm_game.difficulty = 0;
  algorithm_game.level = 0;
  algorithm_game.life = 0;
  algorithm_game.hint = 0;
  algorithm_game.score = 0;
  algorithm_game.status = ALGORITHM_GAME_STOP;
  for (i = 0; i < 8; i++)
    for (j = 0; j < 16; j++)
      algorithm_game.data[i][j] = 0;
  return TRUE;
}

gboolean algorithm_game_begin(gpointer data) {
  /*get a random order of the card image list*/
  if (algorithm_game.status == ALGORITHM_GAME_STOP) {
    switch (GPOINTER_TO_INT(data)) {
    case 1:
      algorithm_game.row = 6;
      algorithm_game.col = 12;
      algorithm_game.difficulty = 0;
      algorithm_game.level = 0;
      algorithm_game.life = 2;
      algorithm_game.hint = 4;
      algorithm_game.score = 0;
      break;
    case 2:
      algorithm_game.row = 7;
      algorithm_game.col = 14;
      algorithm_game.difficulty = 1;
      algorithm_game.level = 0;
      algorithm_game.life = 3;
      algorithm_game.hint = 6;
      algorithm_game.score = 0;
      break;
    case 3:
      algorithm_game.row = 8;
      algorithm_game.col = 16;
      algorithm_game.difficulty = 2;
      algorithm_game.level = 0;
      algorithm_game.life = 4;
      algorithm_game.hint = 8;
      algorithm_game.score = 0;
      break;
    default:

      algorithm_game.row = 8;
      algorithm_game.col = 16;
      algorithm_game.difficulty = 2;
      algorithm_game.level = 0;
      algorithm_game.life = 4;
      algorithm_game.hint = 5;
      algorithm_game.score = 0;
    }
    algorithm_init_data();
    algorithm_game.status = ALGORITHM_GAME_RUN;
    return TRUE;
  } else {
    return FALSE;
  }
}

void algorithm_init_data(void) {
  gint picture_type = 36;
  gint i, j = 128;
  time_t t;
  GSList *picture_list = NULL, *tmp_node; /*Single list*/

  switch (algorithm_game.difficulty) {
  case 0:
    picture_type = 21;
    j = 72;
    break;
  case 1:
    picture_type = 25;
    j = 98;
    break;
  case 2:
    picture_type = 32;
    j = 128;
    break;
  default: /*assert not reach*/
    break;
  }
  for (i = 0; i < j; i++) {
    picture_list = g_slist_prepend(picture_list, GINT_TO_POINTER(i / 4 + 1));
  }
  srand((unsigned)time(&t));
  while (picture_list != NULL) {
    i = rand() % j;
    if (i == 0)
      i = 1;
    /*i get a value within 0-j,so should exclude the situation of 0.
      and rand()/0 is illegal,so should not use rand()/(j-1) to exclude 0*/
    i--; /*switch to 0 based value.*/
    algorithm_game
        .data[(j - 1) / algorithm_game.col][(j - 1) % algorithm_game.col] =
        GPOINTER_TO_INT(g_slist_nth_data(picture_list, i));
    if (i == 0) {
      tmp_node = picture_list;
      picture_list = picture_list->next;
      tmp_node->next = NULL; /*close the node's next node pointer,and so get a 1
                                node single list,and then free it.*/
      g_slist_free(tmp_node); /*free the single list.*/
    } else {
      tmp_node = g_slist_nth(picture_list, i);
      g_slist_nth(picture_list, i - 1)->next = tmp_node->next;
      tmp_node->next = NULL; /*close the node's next node pointer,and so get a 1
                                node single list,and then free it.*/
      g_slist_free(tmp_node); /*free the single list*/
    }
    j--;
  }
}

/*
  test if p1 and p2 can direct link or not. that is to say,the points between p1
  and p2 at the same row or column are all empty. BE CARE:this function do not
  warrant p1 and p2 have the same type of image.
*/
gboolean algorithm_can_direct_link(GdkPoint p1, GdkPoint p2) {
  /*  if(p1.x > 0 && p1.x < algorithm_game.row && p1.y > 0 && p1.y <
    algorithm_game.col
      && p2.x > 0 && p2.x < algorithm_game.row && p2.y > 0 && p2.y <
    algorithm_game.col) g_assert(algorithm_game.data[p1.x][p1.y] ==
    algorithm_game.data[p2.x][p2.y]);
  */
  /*g_print("Direct Link,x1: %d, y1: %d , x2: %d, y2:%d
   * \n",p1.x,p1.y,p2.x,p2.y);*/
  if (p1.x == p2.x || p1.y == p2.y) {
    gint i;
    if (abs(p1.x - p2.x) + abs(p1.y - p2.y) <= 1) {
      return TRUE;
    } else {
      if (p1.x == p2.x && p1.x > -1 && p1.x < algorithm_game.row) {
        if (p1.y > p2.y) {
          for (i = p2.y + 1; i < p1.y; i++) {
            if (algorithm_game.data[p1.x][i] > 0)
              return FALSE;
          }
        } else {
          for (i = p1.y + 1; i < p2.y; i++) {
            if (algorithm_game.data[p1.x][i] > 0)
              return FALSE;
          }
        }
      } else if (p1.y == p2.y && p1.y > -1 && p1.y < algorithm_game.col) {
        if (p1.x > p2.x) {
          for (i = p2.x + 1; i < p1.x; i++) {
            if (algorithm_game.data[i][p1.y] > 0)
              return FALSE;
          }
        } else {
          for (i = p1.x + 1; i < p2.x; i++) {
            if (algorithm_game.data[i][p1.y] > 0)
              return FALSE;
          }
        }
      }
      return TRUE;
    }
  } else {
    return FALSE;
  }
}

/*
  test if p1 and p2 can link.
  first,test if p1 and p2 can direct link,if not,get p1's and p2's adjacent
  empty points at x and y direction, judge if the p1's adjacent empty point can
  direct link to p2's
*/
gboolean algorithm_can_link(GdkPoint p1, GdkPoint p2, GdkPoint *pp3,
                            GdkPoint *pp4) {
  if (algorithm_game.data[p1.x][p1.y] != algorithm_game.data[p2.x][p2.y]) {
    return FALSE;
  }
  if (algorithm_can_direct_link(p1, p2) &&
      pp3 == NULL) /*can direct link,no need to return the turn points.*/
  {
    return TRUE;
  } else {
    /*get adjacent empty points at x and y direction,judge point by point*/
    GSList *p1_list = NULL, *p2_list = NULL;
    p1_list = algorithm_get_points(p1);
    p2_list = algorithm_get_points(p2);
    /*    g_print("length_p1: %d, length_p2: %d
       \n",g_slist_length(p1_list),g_slist_length(p2_list));
        for(i=0;i<g_slist_length(p1_list);i++)
        {
          g_print("point:%d,
       %d",((GdkPoint*)g_slist_nth_data(p1_list,i))->x,((GdkPoint*)g_slist_nth_data(p1_list,i))->y);
        }
        g_print("\n");
        for(j=0;j<g_slist_length(p2_list);j++)
        {
          g_print("point:%d,
       %d",((GdkPoint*)g_slist_nth_data(p2_list,j))->x,((GdkPoint*)g_slist_nth_data(p2_list,j))->y);
        }
        g_print("\n");
    */
    if (p1_list == NULL || p2_list == NULL) {
      return FALSE;
    } else {
      gint i, j;
      for (i = 0; i < g_slist_length(p1_list); i++) {
        for (j = 0; j < g_slist_length(p2_list); j++) {
          if (algorithm_can_direct_link(
                  *(GdkPoint *)g_slist_nth_data(p1_list, i),
                  *(GdkPoint *)g_slist_nth_data(p2_list, j))) {
            if (pp3 != NULL) /* && pp4 != NULL*/
            {
              pp3->x = ((GdkPoint *)g_slist_nth_data(p1_list, i))->x;
              pp3->y = ((GdkPoint *)g_slist_nth_data(p1_list, i))->y;
              pp4->x = ((GdkPoint *)g_slist_nth_data(p2_list, j))->x;
              pp4->y = ((GdkPoint *)g_slist_nth_data(p2_list, j))->y;
            }
            algorithm_free_with_data(p1_list);
            algorithm_free_with_data(p2_list);
            return TRUE;
          }
          /*g_print("can link over.\n"); */
        }
      }
      algorithm_free_with_data(p1_list);
      algorithm_free_with_data(p2_list);
      return FALSE;
    }
  }
}

/*
  free single list and the memory of the data it refer
*/
void algorithm_free_with_data(GSList *list) {
  GSList *last;
  last = list;
  while (last) {
    g_free(last->data);
    last = last->next;
  }
  g_slist_free(list);
}

/*
  find up,down,left and right of point p,get the adjacent empty points,form a
  single list,and return it.
*/
GSList *algorithm_get_points(GdkPoint p) {
  GdkPoint *tmp_point = NULL;
  GSList *p_list = NULL;
  gint i;
  /*g_print("Get Points,x1: %d, y1: %d \n",p.x,p.y);*/
  for (i = p.y + 1; i <= algorithm_game.col; i++) {
    /*p_list = algorithm_game.data[p.x][i] == 0 ? g_slist_prepend(p_list,ddd) :
     * p_list;*/
    if (i < algorithm_game.col && algorithm_game.data[p.x][i] > 0) {
      break;
    } else {
      tmp_point = (GdkPoint *)g_malloc(sizeof(GdkPoint));
      tmp_point->x = p.x;
      tmp_point->y = i;
      p_list = g_slist_prepend(p_list, tmp_point);
    }
  }
  for (i = p.y - 1; i >= -1; i--) {
    /*p_list = algorithm_game.data[p.x][i] == 0 ? g_slist_prepend(p_list,ddd) :
     * p_list;*/
    if (i > -1 && algorithm_game.data[p.x][i] > 0) {
      break;
    } else {
      tmp_point = (GdkPoint *)g_malloc(sizeof(GdkPoint));
      tmp_point->x = p.x;
      tmp_point->y = i;
      p_list = g_slist_prepend(p_list, tmp_point);
    }
  }
  for (i = p.x + 1; i <= algorithm_game.row; i++) {
    /*p_list = algorithm_game.data[p.x][i] == 0 ? g_slist_prepend(p_list,ddd) :
     * p_list;*/
    if (i < algorithm_game.row && algorithm_game.data[i][p.y] > 0) {
      break;
    } else {
      tmp_point = (GdkPoint *)g_malloc(sizeof(GdkPoint));
      tmp_point->x = i;
      tmp_point->y = p.y;
      p_list = g_slist_prepend(p_list, tmp_point);
    }
  }
  for (i = p.x - 1; i >= -1; i--) {
    /*p_list = algorithm_game.data[p.x][i] == 0 ? g_slist_prepend(p_list,ddd) :
     * p_list;*/
    if (i > -1 && algorithm_game.data[i][p.y] > 0) {
      break;
    } else {
      tmp_point = (GdkPoint *)g_malloc(sizeof(GdkPoint));
      tmp_point->x = i;
      tmp_point->y = p.y;
      p_list = g_slist_prepend(p_list, tmp_point);
    }
  }
  /*in order to efficient the operation of insert node to a single list,above
    algorithm insert node at the front, and then reverse the list,and
    return.MUST reverse,or will not get the right points of turning.
  */
  return g_slist_reverse(p_list);
}

/*
  empty the data of the two points.
*/
void algorithm_link(GdkPoint p1, GdkPoint p2) {
  algorithm_game.data[p1.x][p1.y] = 0;
  algorithm_game.data[p2.x][p2.y] = 0;
  /*add score*/
  algorithm_game.score += 20;
}

/*
  test if the current game situation have solution.
  return value:
  0: yes,have solution.
  1: no,need to shuffle the cards.
  2: the cards are all deleted,this level is clear.
*/
gint algorithm_game_no_solution(void) {
  gint i, j;
  gint k, l;
  gint cards_num = 0;
  /*g_print("================================================================\n");*/
  for (i = 0; i < algorithm_game.row; i++) {
    for (j = 0; j < algorithm_game.col; j++) {
      if (algorithm_game.data[i][j] > 0) {
        cards_num++;
        for (k = i; k < algorithm_game.row; k++) {
          for (l = 0; l < algorithm_game.col; l++) {
            if (k == i && l == j)
              continue; /*exclude the situation of link to itself*/
            if (algorithm_game.data[k][l] > 0) {
              GdkPoint p1, p2;
              p1.x = i;
              p1.y = j;
              p2.x = k;
              p2.y = l;
              if (algorithm_can_link(p1, p2, NULL, NULL)) {
                /*g_print("p1:%d,%d -- p2:%d,%d can
                 * link.\n",p1.x,p1.y,p2.x,p2.y);*/
                return 0;
              }
              /*g_print("p1:%d,%d -- p2:%d,%d can not
               * link.\n",p1.x,p1.y,p2.x,p2.y);*/
            }
          }
        }
      }
    }
  }
  if (cards_num > 0) {
    return 1;
  }
  return 2;
}

/*
  shuffle cards.
  read the remain cards in data array,form a single list.then traversal the data
  array, at every point that have cards,get a random card from the single list
  and put it there. BE CARE: the life value will be minimised in UI dealing
  function,because in this function, shuffle one time do not certainly get a
  game situation that have solution,so this function may be called more than one
  time.
*/
static void algorithm_game_shuffle_inner(size_t seed) {
  GSList *picture_list = NULL, *tmp_node;
  gint i, j;
  for (i = 0; i < algorithm_game.row; i++) {
    for (j = 0; j < algorithm_game.col; j++) {
      if (algorithm_game.data[i][j] > 0) {
        picture_list = g_slist_prepend(
            picture_list, GINT_TO_POINTER(algorithm_game.data[i][j]));
      }
    }
  }
  srand(seed);
  for (i = 0; i < algorithm_game.row; i++) {
    for (j = 0; j < algorithm_game.col; j++) {
      if (algorithm_game.data[i][j] > 0) {
        gint m = rand() % g_slist_length(picture_list);
        if (m == 0)
          m = 1;
        m--;
        tmp_node = g_slist_nth(picture_list, m);
        algorithm_game.data[i][j] = GPOINTER_TO_INT(tmp_node->data);
        if (m == 0) {
          picture_list = picture_list->next;
          tmp_node->next = NULL;
          g_slist_free(tmp_node);
        } else {
          g_slist_nth(picture_list, m - 1)->next = tmp_node->next;
          tmp_node->next = NULL;
          g_slist_free(tmp_node);
        }
      }
    }
  }
}

void algorithm_game_shuffle(void) {
  time_t t = 0;
  size_t base_seed = (unsigned)time(&t);
  do {
    algorithm_game_shuffle_inner(++base_seed);
  }
  while (algorithm_game_no_solution() == 1);
  /*recursion call of this function,untill get a game situation that have
   * solution.*/
}

void algorithm_game_change(GdkPoint p1, GdkPoint p2) {
  switch (algorithm_game.level) {
  case 0: /*No Change*/
    algorithm_data_change_0(p1, p2);
    break;
  case 1: /*Move Down*/
    algorithm_data_change_1(p1, p2);
    break;
  case 2: /*Move Left*/
    algorithm_data_change_2(p1, p2);
    break;
  case 3: /*Up Down Separate*/
    algorithm_data_change_3(p1, p2);
    break;
  case 4: /*Left and Right Separate*/
    algorithm_data_change_4(p1, p2);
    break;
  case 5: /*Up and Down Converge*/
    algorithm_data_change_5(p1, p2);
    break;
  case 6: /*Left and Right Converge*/
    algorithm_data_change_6(p1, p2);
    break;
  case 7: /*Up leftward,Down rightward*/
    algorithm_data_change_7(p1, p2);
    break;
  case 8: /*Left downward,Right upward*/
    algorithm_data_change_8(p1, p2);
    break;
  case 9: /*Disperse from Center*/
    algorithm_data_change_9(p1, p2);
    break;
  case 10: /*Centralize*/
    algorithm_data_change_10(p1, p2);
    break;
  default:
    /*assert not reach*/
    __builtin_unreachable();
    break;
  }
}

gboolean algorithm_game_net_level(void) {
  if (algorithm_game.level >= 10) /*11 Levels,from 0 to 10*/
  {
    return FALSE;
  } else {
    algorithm_game.level++;
    algorithm_game.life += 1;
    algorithm_game.hint += 1;
    algorithm_game.score += algorithm_game.level > 5
                                ? 400 * algorithm_game.level
                                : 200 * algorithm_game.level;
    algorithm_game.score +=
        algorithm_game.life * 100 + algorithm_game.hint * 50;
    algorithm_init_data();
    return TRUE;
  }
}
/*No Change, do nothing*/
void algorithm_data_change_0(GdkPoint p1, GdkPoint p2) { /*do nothing*/
}
/*Move Down*/
void algorithm_data_change_1(GdkPoint p1, GdkPoint p2) {
  gint i;
  for (i = p1.x; i > 0; i--) {
    algorithm_game.data[i][p1.y] = algorithm_game.data[i - 1][p1.y];
  }
  algorithm_game.data[0][p1.y] = 0;
  i = p2.x;
  if (p1.y == p2.y && p1.x > p2.x)
    i++;
  for (; i > 0; i--) {
    algorithm_game.data[i][p2.y] = algorithm_game.data[i - 1][p2.y];
  }
  algorithm_game.data[0][p2.y] = 0;
}
/*Move Left*/
void algorithm_data_change_2(
    GdkPoint p1,
    GdkPoint p2) { /*BE CARE: the last column do not in the for loop.*/
  gint j;
  for (j = p1.y; j < algorithm_game.col - 1; j++) {
    algorithm_game.data[p1.x][j] = algorithm_game.data[p1.x][j + 1];
  }
  algorithm_game.data[p1.x][algorithm_game.col - 1] = 0;
  j = p2.y;
  if (p1.x == p2.x && p1.y < p2.y)
    j--;
  for (; j < algorithm_game.col - 1; j++) {
    algorithm_game.data[p2.x][j] = algorithm_game.data[p2.x][j + 1];
  }
  algorithm_game.data[p2.x][algorithm_game.col - 1] = 0;
}
/*Up and Down Separate*/
void algorithm_data_change_3(GdkPoint p1, GdkPoint p2) {
  gint i;
  gint tmp_start, tmp_end;

  tmp_start = p1.x;
  tmp_end = algorithm_game.row / 2;
  if (p1.x < algorithm_game.row / 2)
    tmp_end--;
  i = tmp_start;
  if (tmp_start != tmp_end) {
    while (i != tmp_end) {
      gint sign = (tmp_end - tmp_start) / abs(tmp_end - tmp_start);
      algorithm_game.data[i][p1.y] = algorithm_game.data[i + sign][p1.y];
      algorithm_game.data[i + sign][p1.y] = 0;
      i = i + sign;
    }
  }

  tmp_start = p2.x;
  tmp_end = algorithm_game.row / 2;
  if (p2.x < algorithm_game.row / 2)
    tmp_end--;
  if (p1.y == p2.y) /*p1 and p2 are in the same column*/
  {
    if (p1.x < algorithm_game.row / 2 &&
        p2.x < algorithm_game.row / 2) /*p1 and p2 are all in the up half rows*/
    {
      if (p1.x < p2.x) /*p1's move will change p2's positon*/
      {
        tmp_start--; /*start position move up*/
      }
    } else if (p1.x >= algorithm_game.row / 2 &&
               p2.x >= algorithm_game.row /
                           2) /*p1 and p2 are all in  the down half rows*/
    {
      if (p1.x > p2.x) {
        tmp_start++;
      }
    }
  }
  i = tmp_start;
  if (tmp_start != tmp_end) {
    while (i != tmp_end) {
      gint sign = (tmp_end - tmp_start) / abs(tmp_end - tmp_start);
      algorithm_game.data[i][p2.y] = algorithm_game.data[i + sign][p2.y];
      algorithm_game.data[i + sign][p2.y] = 0;
      i = i + sign;
    }
  }
}
/*Left and Right Separate*/
void algorithm_data_change_4(GdkPoint p1, GdkPoint p2) {
  gint j;
  gint tmp_start, tmp_end;

  tmp_start = p1.y;
  tmp_end = algorithm_game.col / 2;
  if (p1.y < algorithm_game.col / 2)
    tmp_end--;
  j = tmp_start;
  if (tmp_start != tmp_end) {
    while (j != tmp_end) {
      gint sign = (tmp_end - tmp_start) / abs(tmp_end - tmp_start);
      algorithm_game.data[p1.x][j] = algorithm_game.data[p1.x][j + sign];
      algorithm_game.data[p1.x][j + sign] = 0;
      j = j + sign;
    }
  }

  tmp_start = p2.y;
  tmp_end = algorithm_game.col / 2;
  if (p2.y < algorithm_game.col / 2)
    tmp_end--;
  if (p1.x == p2.x) {
    if (p1.y < algorithm_game.col / 2 && p2.y < algorithm_game.col / 2) {
      if (p1.y < p2.y) {
        tmp_start--;
      }
    } else if (p1.y >= algorithm_game.col / 2 &&
               p2.y >= algorithm_game.col / 2) {
      if (p1.y > p2.y) {
        tmp_start++;
      }
    }
  }
  j = tmp_start;
  if (tmp_start != tmp_end) {
    while (j != tmp_end) {
      gint sign = (tmp_end - tmp_start) / abs(tmp_end - tmp_start);
      algorithm_game.data[p2.x][j] = algorithm_game.data[p2.x][j + sign];
      algorithm_game.data[p2.x][j + sign] = 0;
      j = j + sign;
    }
  }
}
/*Up and Down Converge*/
void algorithm_data_change_5(GdkPoint p1, GdkPoint p2) {
  gint i;
  gint tmp_start, tmp_end;

  tmp_start = p1.x;
  if (p1.x < algorithm_game.row / 2) /* <= row/2 -1 */
  {
    tmp_end = 0;
  } else {
    tmp_end = algorithm_game.row - 1;
  }
  i = tmp_start;
  if (tmp_start != tmp_end) {
    while (i != tmp_end) {
      gint sign = (tmp_end - tmp_start) / abs(tmp_end - tmp_start);
      algorithm_game.data[i][p1.y] = algorithm_game.data[i + sign][p1.y];
      algorithm_game.data[i + sign][p1.y] = 0;
      i = i + sign;
    }
  }

  tmp_start = p2.x;
  if (p2.x < algorithm_game.row / 2) {
    tmp_end = 0;
  } else {
    tmp_end = algorithm_game.row - 1;
  }
  if (p1.y == p2.y) /*同p1 and p2 are in the same column*/
  {
    if (p1.x < algorithm_game.row / 2 &&
        p2.x < algorithm_game.row / 2) /*p1 and p2 are all in the up half rows*/
    {
      if (p1.x > p2.x) /*p1's move will change p2's positon*/
      {
        tmp_start++; /*start positon move down*/
      }
    } else if (p1.x >= algorithm_game.row / 2 &&
               p2.x >= algorithm_game.row /
                           2) /*p1 and p2 are all in the down half rows*/
    {
      if (p1.x < p2.x) {
        tmp_start--;
      }
    }
  }
  i = tmp_start;
  if (tmp_start != tmp_end) {
    while (i != tmp_end) {
      gint sign = (tmp_end - tmp_start) / abs(tmp_end - tmp_start);
      algorithm_game.data[i][p2.y] = algorithm_game.data[i + sign][p2.y];
      algorithm_game.data[i + sign][p2.y] = 0;
      i = i + sign;
    }
  }
}
/*Left and Right Converge*/
void algorithm_data_change_6(GdkPoint p1, GdkPoint p2) {
  gint j;
  gint tmp_start, tmp_end;

  tmp_start = p1.y;
  if (p1.y < algorithm_game.col / 2) {
    tmp_end = 0;
  } else {
    tmp_end = algorithm_game.col - 1;
  }
  j = tmp_start;
  if (tmp_start != tmp_end) {
    while (j != tmp_end) {
      gint sign = (tmp_end - tmp_start) / abs(tmp_end - tmp_start);
      algorithm_game.data[p1.x][j] = algorithm_game.data[p1.x][j + sign];
      algorithm_game.data[p1.x][j + sign] = 0;
      j = j + sign;
    }
  }

  tmp_start = p2.y;
  if (p2.y < algorithm_game.col / 2) {
    tmp_end = 0;
  } else {
    tmp_end = algorithm_game.col - 1;
  }
  if (p1.x == p2.x) {
    if (p1.y < algorithm_game.col / 2 && p2.y < algorithm_game.col / 2) {
      if (p1.y > p2.y) {
        tmp_start++;
      }
    } else if (p1.y >= algorithm_game.col / 2 &&
               p2.y >= algorithm_game.col / 2) {
      if (p1.y < p2.y) {
        tmp_start--;
      }
    }
  }
  j = tmp_start;
  if (tmp_start != tmp_end) {
    while (j != tmp_end) {
      gint sign = (tmp_end - tmp_start) / abs(tmp_end - tmp_start);
      algorithm_game.data[p2.x][j] = algorithm_game.data[p2.x][j + sign];
      algorithm_game.data[p2.x][j + sign] =
          0; // this sentence can be write outside of while loop in some way.
      j = j + sign;
    }
  }
}
/*Up leftward,Down rightward*/
void algorithm_data_change_7(GdkPoint p1, GdkPoint p2) {
  gint j;
  if (p1.x < algorithm_game.row / 2) /*leftward*/
  {
    for (j = p1.y; j < algorithm_game.col - 1; j++) {
      algorithm_game.data[p1.x][j] = algorithm_game.data[p1.x][j + 1];
    }
    algorithm_game.data[p1.x][algorithm_game.col - 1] = 0;
  } else /*rightward*/
  {
    for (j = p1.y; j > 0; j--) {
      algorithm_game.data[p1.x][j] = algorithm_game.data[p1.x][j - 1];
    }
    algorithm_game.data[p1.x][0] = 0;
  }
  j = p2.y;
  if (p2.x < algorithm_game.row / 2) /*leftward*/
  {
    if (p1.x == p2.x && p1.y < p2.y)
      j--;
    for (; j < algorithm_game.col - 1; j++) {
      algorithm_game.data[p2.x][j] = algorithm_game.data[p2.x][j + 1];
    }
    algorithm_game.data[p2.x][algorithm_game.col - 1] = 0;
  } else /*rightward*/
  {
    if (p1.x == p2.x && p1.y > p2.y)
      j++;
    for (; j > 0; j--) {
      algorithm_game.data[p2.x][j] = algorithm_game.data[p2.x][j - 1];
    }
    algorithm_game.data[p2.x][0] = 0;
  }
}
/*Left downward,Right upward*/
void algorithm_data_change_8(GdkPoint p1, GdkPoint p2) {
  gint i;
  if (p1.y < algorithm_game.col / 2) /*downward*/
  {
    for (i = p1.x; i > 0; i--) {
      algorithm_game.data[i][p1.y] = algorithm_game.data[i - 1][p1.y];
    }
    algorithm_game.data[0][p1.y] = 0;
  } else /*upward*/
  {
    for (i = p1.x; i < algorithm_game.row - 1; i++) {
      algorithm_game.data[i][p1.y] = algorithm_game.data[i + 1][p1.y];
    }
    algorithm_game.data[algorithm_game.row - 1][p1.y] = 0;
  }
  i = p2.x;
  if (p2.y < algorithm_game.col / 2) /*downward*/
  {
    if (p1.y == p2.y && p1.x > p2.x)
      i++;
    for (; i > 0; i--) {
      algorithm_game.data[i][p2.y] = algorithm_game.data[i - 1][p2.y];
    }
    algorithm_game.data[0][p2.y] = 0;
  } else /*upward*/
  {
    if (p1.y == p2.y && p1.x < p2.x)
      i--;
    for (; i < algorithm_game.row - 1; i++) {
      algorithm_game.data[i][p2.y] = algorithm_game.data[i + 1][p2.y];
    }
    algorithm_game.data[algorithm_game.row - 1][p2.y] = 0;
  }
}
/*
  Disperse from Center
  first,left and right seperate,and then up and down seperate.
*/
void algorithm_data_change_9(GdkPoint p1, GdkPoint p2) {
  GdkPoint p3, p4;
  gint sign;
  algorithm_data_change_4(p1, p2); /*1.left and right seperate*/
  /*find p1,p2 's position after 'left and right seperate',then do 'up and down
   * seperate' on p1,p2 's new position*/
  p3.x = p1.x;
  p3.y = (p1.y < algorithm_game.col / 2) ? 0 : (algorithm_game.col - 1);
  sign = p3.y ? -1 : 1;
  while (algorithm_game.data[p3.x][p3.y] != 0) {
    p3.y = p3.y + sign;
  }

  p4.x = p2.x;
  p4.y = (p2.y < algorithm_game.col / 2) ? 0 : (algorithm_game.col - 1);
  sign = p4.y ? -1 : 1;
  while (algorithm_game.data[p4.x][p4.y] != 0) {
    p4.y = p4.y + sign;
  }
  /*modify in case of special situation*/
  if (p1.x == p2.x) {
    if (p1.y < algorithm_game.col / 2 && p2.y < algorithm_game.col / 2) {
      p4.y = p3.y + 1;
    } else if (p1.y >= algorithm_game.col / 2 &&
               p2.y >= algorithm_game.col / 2) {
      p4.y = p3.y - 1;
    }
  }
  /*p3,p4 are the new position of p1,p2 after 'left and right seperate',
    do 'up and down seperate' on them*/
  algorithm_data_change_3(p3, p4);
}
/*
  Centralize
  first do 'Left Right Converge' and then 'Up Down Converge'
*/
void algorithm_data_change_10(GdkPoint p1, GdkPoint p2) {
  GdkPoint p3, p4;
  gint sign;
  algorithm_data_change_6(p1, p2); /*first do 'Left Right Converge'*/
  /*find the new position of p1,p2 after 'Left Right Converge',then do 'Up Down
   * Converge' on new position*/
  p3.x = p1.x;
  p3.y = (p1.y < algorithm_game.col / 2) ? (algorithm_game.col / 2 - 1)
                                         : (algorithm_game.col / 2);
  sign = (p1.y < algorithm_game.col / 2) ? -1 : 1;
  while (algorithm_game.data[p3.x][p3.y] != 0) {
    p3.y = p3.y + sign;
  }

  p4.x = p2.x;
  p4.y = (p2.y < algorithm_game.col / 2) ? (algorithm_game.col / 2 - 1)
                                         : (algorithm_game.col / 2);
  sign = (p2.y < algorithm_game.col / 2) ? -1 : 1;
  while (algorithm_game.data[p4.x][p4.y] != 0) {
    p4.y = p4.y + sign;
  }
  /*modify in case of special situation*/
  if (p1.x == p2.x) {
    if (p1.y < algorithm_game.col / 2 && p2.y < algorithm_game.col / 2) {
      p4.y = p3.y - 1;
    } else if (p1.y >= algorithm_game.col / 2 &&
               p2.y >= algorithm_game.col / 2) {
      p4.y = p3.y + 1;
    }
  }
  /*p3,p4 are the new position of p1,p2 after 'Left Right Converge',
    do 'Up Down Converge' on them*/
  algorithm_data_change_5(p3, p4);
}
