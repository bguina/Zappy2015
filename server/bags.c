/*
** bags.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:18:20 2012 nathan irjud
** Last update Sun Jul 15 17:18:21 2012 nathan irjud
*/

#include <string.h>
#include <stdio.h>

#include "server.h"

static int	get_index_from_name(char *name)
{
  if (strcmp(name, "nourriture") == 0)
    return (FOOD);
  if (strcmp(name, "linemate") == 0)
    return (LINEMATE);
  if (strcmp(name, "deraumere") == 0)
    return (DERAUMERE);
  if (strcmp(name, "sibur") == 0)
    return (SIBUR);
  if (strcmp(name, "mendiane") == 0)
    return (MENDIANE);
  if (strcmp(name, "phiras") == 0)
    return (PHIRAS);
  if (strcmp(name, "thystame") == 0)
    return (THYSTAME);
  return (-1);
}

void		inventaire(t_server *s, t_player *p, char *param)
{
  static char	str[500];

  (void)s;
  (void)param;
  memset(str, 0, 500);
  sprintf(str,"{nourriture %d,\
linemate %d,deraumere %d,sibur %d,mendiane %d,phiras %d,thystame %d}\n",
	  p->bag[FOOD],
	  p->bag[LINEMATE],
	  p->bag[DERAUMERE],
	  p->bag[SIBUR],
	  p->bag[MENDIANE],
	  p->bag[PHIRAS],
	  p->bag[THYSTAME]);
  communication_sendto(p->client_data, str, 1);
}

void		prend(t_server *s, t_player *p, char *param)
{
  static char	str[500];
  int		obj;

  obj = get_index_from_name(param);
  if (obj == -1 || s->game.map[p->x + p->y * s->x].objects[obj] == 0)
    communication_sendto(p->client_data, "ko\n", 1);
  else
    {
      memset(str, 0, 500);
      if (obj == FOOD)
	s->game.current_food -= 1;
      s->game.map[p->x + p->y * s->x].objects[obj] -= 1;
      p->bag[obj] += 1;
      sprintf(str, "pgt %d %d\n", p->id, obj);
      communication_sendto(p->client_data, "ok\n", 1);
      communication_broadcast(s->display_list, str);
      request_broadcast(s, pin, p->id, 0);
      request_broadcast(s, bct, p->x, p->y);
    }
}

void		pose(t_server *s, t_player *p, char *param)
{
  static char	str[500];
  int		obj;

  obj = get_index_from_name(param);
  if (obj == -1 || p->bag[obj] == 0)
    communication_sendto(p->client_data, "ko\n", 1);
  else
    {
      memset(str, 0, 500);
      if (obj == FOOD)
	s->game.current_food += 1;
      p->bag[obj] -= 1;
      s->game.map[p->x + p->y * s->x].objects[obj] += 1;
      sprintf(str, "pdr %d %d\n", p->id, obj);
      communication_sendto(p->client_data, "ok\n", 1);
      communication_broadcast(s->display_list, str);
      request_broadcast(s, pin, p->id, 0);
      request_broadcast(s, bct, p->x, p->y);
    }
}

