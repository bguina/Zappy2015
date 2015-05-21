/*
** move.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:27:00 2012 nathan irjud
** Last update Sun Jul 15 17:27:21 2012 nathan irjud
*/

#include "server.h"

void		remove_from_map(t_server *s, t_player *p)
{
  t_player	*tmp;

  tmp = s->game.map[p->x + p->y * s->x].players;
  if (tmp == p)
    s->game.map[p->x + p->y * s->x].players =
      s->game.map[p->x + p->y * s->x].players->next_t;
  else
    {
      while (tmp->next_t != p)
	tmp = tmp->next_t;
      tmp->next_t = p->next_t;
    }
}

void		avance(t_server *s, t_player *p, char *param)
{
  (void)param;
  remove_from_map(s, p);
  if (p->dir == NORTH)
    p->y = (p->y - 1 + s->y) % s->y;
  else if (p->dir == EAST)
    p->x = (p->x + 1) % s->x;
  else if (p->dir == SOUTH)
    p->y = (p->y + 1) % s->y;
  else
    p->x = (p->x - 1 + s->x) % s->x;
  p->next_t = s->game.map[p->x + p->y * s->x].players;
  s->game.map[p->x + p->y * s->x].players = p;
  communication_sendto(p->client_data, "ok\n", 1);
  request_broadcast(s, ppo, p->id, 0);
}

void		droite(t_server *s, t_player *p, char *param)
{
  (void)param;
  p->dir = (p->dir % 4) + 1;
  communication_sendto(p->client_data, "ok\n", 1);
  request_broadcast(s, ppo, p->id, 0);
}

void		gauche(t_server *s, t_player *p, char *param)
{
  (void)param;
  p->dir = ((p->dir + 4 - 2) % 4) + 1;
  communication_sendto(p->client_data, "ok\n", 1);
  request_broadcast(s, ppo, p->id, 0);
}

