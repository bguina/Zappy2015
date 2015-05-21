/*
** expulse.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:21:55 2012 nathan irjud
** Last update Sun Jul 15 17:25:48 2012 nathan irjud
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

static void	update_expulsed(t_server *s, t_tile *t,
				t_player *front, t_player *p)
{
  t_player	*tmp;
  t_player	*back;
  static char	str[500];

  tmp = front;
  while (tmp)
    {
      if (p->dir == NORTH)
	tmp->y = (p->y - 1 + s->y) % s->y;
      else if (p->dir == EAST)
	tmp->x = (p->x + 1) % s->x;
      else if (p->dir == SOUTH)
	tmp->y = (p->y + 1) % s->y;
      else
	tmp->x = (p->x - 1 + s->x) % s->x;
      memset(str, 0, 500);
      sprintf(str, "deplacement: %d\n", get_dir(s, tmp, p->x, p->y));
      communication_sendto(tmp->client_data, str, 0);
      request_broadcast(s, ppo, tmp->id, 0);
      back = tmp;
      tmp = tmp->next_t;
    }
  back->next_t = t->players;
  t->players = front;
}

static void	remove_player(t_player **front, t_player **tmp, t_player *p)
{
  if (*front == p)
    *front = p->next_t;
  else
    {
      *tmp = *front;
      while ((*tmp)->next_t != p)
	*tmp = (*tmp)->next_t;
      (*tmp)->next_t = p->next_t;
      while ((*tmp)->next_t)
	*tmp = (*tmp)->next_t;
    }
}

void		expulse(t_server *s, t_player *p, char *param)
{
  t_player	*front;
  t_player	*tmp;
  t_tile	*tile;
  static char	str[500];

  (void)param;
  if (p->next_t == NULL && s->game.map[p->x + p->y * s->x].players == p)
    communication_sendto(p->client_data, "ko\n", 1);
  else
    {
      front = s->game.map[p->x + p->y * s->x].players;
      remove_player(&front, &tmp, p);
      tile = get_front_tile(s, p);
      p->next_t = NULL;
      update_expulsed(s, tile, front, tmp);
      s->game.map[p->x + p->y * s->x].players = p;
      communication_sendto(p->client_data, "ok\n", 1);
      memset(str, 0, 500);
      sprintf(str, "pex %d\n", p->id);
      communication_broadcast(s->display_list, str);
    }
}

