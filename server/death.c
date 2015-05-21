/*
** death.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:21:46 2012 nathan irjud
** Last update Sun Jul 15 17:25:17 2012 nathan irjud
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"

static void	drop_ressources(t_server *s, t_player *p)
{
  int		i;

  i = 0;
  while (++i < NB_OBJECTS)
    gen_rsc(s, i, p->bag[i]);
}

void		player_death(t_server *s, t_player *p)
{
  static char	str[500];

  remove_from_map(s, p);
  drop_ressources(s, p);
  s->game.players[p->id] = NULL;
  memset(str, 0, 500);
  sprintf(str, "pdi %d\n", p->id);
  communication_broadcast(s->display_list, str);
  s->teams[p->team_idx].member_nb -= 1;
  p->client_data->player_data = NULL;
  communication_sendto(p->client_data, "mort\n", 0);
  p->client_data->must_die = 1;
  free(p);
}

void		ghost_death(t_server *s, t_player *p)
{
  static char	str[500];
  t_player	*tmp;

  remove_from_map(s, p);
  drop_ressources(s, p);
  tmp = s->game.ghosts;
  if (tmp == p)
    s->game.ghosts = tmp->next_g;
  else
    while (tmp->next_g)
      {
	if (tmp->next_g == p)
	  tmp->next_g = p->next_g;
	tmp = tmp->next_g;
      }
  memset(str, 0, 500);
  sprintf(str, "pdi %d\n", p->id);
  communication_broadcast(s->display_list, str);
  s->teams[p->team_idx].member_nb -= 1;
  free(p);
}

void		egg_death(t_server *s, t_egg *e)
{
  static char	str[500];
  t_egg		*tmp;

  tmp = s->game.eggs;
  if (tmp == e)
    s->game.eggs = tmp->next;
  else
    while (tmp && tmp->next)
      {
	if (tmp->next == e)
	  tmp->next = e->next;
	tmp = tmp->next;
      }
  memset(str, 0, 500);
  sprintf(str, "edi %d\n", e->id);
  communication_broadcast(s->display_list, str);
  free(e);
}
