/*
** voir.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:23:50 2012 nathan irjud
** Last update Sun Jul 15 17:30:11 2012 nathan irjud
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"

static void	get_first_tile(int i, t_player *p, t_server *s, int *coor)
{
  if (p->dir == NORTH)
    {
      coor[0] = (p->x - i + s->x) % s->x;
      coor[1] = (p->y - i + s->y) % s->y;
    }
  else if (p->dir == EAST)
    {
      coor[0] = (p->x + i) % s->x;
      coor[1] = (p->y - i + s->y) % s->y;
    }
  else if (p->dir == SOUTH)
    {
      coor[0] = (p->x + i) % s->x;
      coor[1] = (p->y + i) % s->y;
    }
  else
    {
      coor[0] = (p->x - i + s->x) % s->x;
      coor[1] = (p->y + i) % s->y;
    }
}

static t_tile	*tile_sum(int *coor, t_server *s, int j, t_player *p)
{
  int		x;
  int		y;

  x = coor[0];
  y = coor[1];
  if (p->dir == NORTH)
    x = (x + j) % s->x;
  else if (p->dir == EAST)
    y = (y + j) % s->y;
  else if (p->dir == SOUTH)
    x = (x - j + s->x) % s->x;
  else
    y = (y - j + s->y) % s->y;
  return (&(s->game.map[x + y * s->x]));
}

static void	dump_tile(char *str, t_tile *t)
{
  t_player	*tmp;

  tmp = t->players;
  while (tmp)
    {
      append_text(str, " joueur", 1);
      tmp = tmp->next_t;
    }
  append_text(str, " nourriture", t->objects[FOOD]);
  append_text(str, " linemate", t->objects[LINEMATE]);
  append_text(str, " deraumere", t->objects[DERAUMERE]);
  append_text(str, " sibur", t->objects[SIBUR]);
  append_text(str, " mendiane", t->objects[MENDIANE]);
  append_text(str, " phiras", t->objects[PHIRAS]);
  append_text(str, " thystame", t->objects[THYSTAME]);
}

static void	iter_on_tiles(t_server *s, t_player *p, char *str)
{
  int		i;
  int		j;
  int		coor[2];

  i = -1;
  str[0] = '{';
  while (++i <= p->level)
    {
      get_first_tile(i, p, s, &coor[0]);
      j = -1;
      while (++j < 2 * i + 1)
	{
	  if (j)
	    sprintf(str, "%s,", str);
	  dump_tile(&str[0], tile_sum(&coor[0], s, j, p));
	}
      if (i < p->level)
      	sprintf(str, "%s,", str);
    }
}

void		voir(t_server *s, t_player *p, char *param)
{
  char		*str;

  (void)param;
  if ((str = malloc(s->game.current_food * 20 + 5000)) == NULL)
    {
      communication_sendto(p->client_data, "ko\n", 1);
      return;
    }
  memset(str, 0, s->game.current_food * 20 + 5000);
  iter_on_tiles(s, p, str);
  sprintf(str, "%s}\n", str);
  communication_sendto(p->client_data, str, 1);
  free(str);
}

