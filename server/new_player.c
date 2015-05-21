/*
** new_player.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:23:17 2012 nathan irjud
** Last update Sun Jul 15 17:28:18 2012 nathan irjud
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "server.h"

static t_player	*get_new_from_ghosts(t_server *s, int tidx)
{
  t_player	*tmp;
  t_player	*tmp_next;

  if ((tmp = s->game.ghosts) == NULL)
    return (NULL);
  if (tmp->team_idx == tidx)
    {
      s->game.ghosts = tmp->next_g;
      tmp->next_g = NULL;
      return (tmp);
    }
  tmp_next = tmp->next_g;
  while (tmp_next)
    {
      if (tmp_next->team_idx == tidx)
	{
	  tmp->next_g = tmp_next->next_g;
	  tmp_next->next_g = NULL;
	  return (tmp_next);
	}
    }
  return (NULL);
}

static void	delete_egg(t_server *s, t_egg *e)
{
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
  free(e);
}

static int	get_new_from_egg(t_server *s, t_player *new, int tidx)
{
  static char	str[500];
  t_egg		*tmp;

  tmp = s->game.eggs;
  while (tmp)
    {
      if (tmp->born && tmp->team_idx == tidx)
	{
	  new->x = tmp->x;
	  new->y = tmp->y;
	  new->bag[FOOD] = tmp->food;
	  s->teams[tidx].egg_slot_nb -= 1;
	  memset(str, 0, 500);
	  sprintf(str, "ebo %d\n", tmp->id);
	  communication_broadcast(s->display_list, str);
	  delete_egg(s, tmp);
	  return (1);
	}
      tmp = tmp->next;
    }
  return (0);
}

static void	init_new_player(t_server *s, int tidx, t_player *new)
{
  new->x = random() % s->x;
  new->y = random() % s->y;
  new->bag[FOOD] = 10;
  get_new_from_egg(s, new, tidx);
  new->team_idx = tidx;
  new->team = s->teams[tidx].name;
  new->level = 1;
  new->dir = (random() % 4) + 1;
}

int		new_player(t_server *s, t_client *c, int tidx)
{
  static int	id = 0;
  t_player	*new;

  if ((new = get_new_from_ghosts(s, tidx)) == NULL)
    {
      if ((new = malloc(sizeof(t_player))) == NULL)
	return (1);
      memset(new, 0, sizeof(t_player));
      new->id = ++id;
      init_new_player(s, tidx, new);
      new->next_t = s->game.map[new->x + new->y * s->x].players;
      s->game.map[new->x + new->y * s->x].players = new;
    }
  s->teams[tidx].member_nb += 1;
  new->client_data = c;
  c->player_data = new;
  s->game.players[new->id] = new;
  request_broadcast(s, pnw, new->id, 0);
  request_broadcast(s, pin, new->id, 0);
  return (0);
}

