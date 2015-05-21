/*
** new_action.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:23:07 2012 nathan irjud
** Last update Sun Jul 15 17:27:50 2012 nathan irjud
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"

void		insert_action_in_queue(t_server *s, t_action *new)
{
  t_action	*tmp;

  if (s->game.actions == NULL)
    s->game.actions = new;
  else
    {
      tmp = s->game.actions;
      if (timercmp(&tmp->time, &new->time, >))
	{
	  new->next = tmp;
	  s->game.actions = new;
	}
      else
	while (tmp->next)
	  {
	    if (timercmp(&tmp->next->time, &new->time, >))
	      {
		new->next = tmp->next;
		tmp->next = new;
		return;
	      }
	    tmp = tmp->next;
	  }
      if (!tmp->next && s->game.actions != new)
	tmp->next = new;
    }
  new->player->busy = 1;
}

static void	set_action_time(t_server *s, t_player *p,
				struct timeval *t, int cmd_idx)
{
  gettimeofday(t, NULL);
  while (t->tv_usec < 0)
    {
      t->tv_usec += 100000;
      t->tv_sec -= 1;
    }
  if (p->busy)
    {
      t->tv_sec = (s->commands[cmd_idx].nb_cycle * 1000000 / s->f) / 1000000;
      t->tv_usec = (s->commands[cmd_idx].nb_cycle * 1000000 / s->f) % 1000000;
    }
  else
    {
      t->tv_sec += (s->commands[cmd_idx].nb_cycle * 1000000 / s->f) / 1000000;
      t->tv_usec += (s->commands[cmd_idx].nb_cycle * 1000000 / s->f) % 1000000;
    }
  while (t->tv_usec >= 1000000)
    {
      t->tv_usec -= 1000000;
      t->tv_sec += 1;
    }
}

static int	handle_incant(t_server *s, t_player *p)
{
  t_player	*tmp;
  static char	str[500];

  if (incantation_valide(s, p) == 0)
    {
      communication_sendto(p->client_data, "ko\n", 1);
      return (0);
    }
  memset(str, 0, 500);
  sprintf(str, "pic %d %d %d %d", p->x, p->y, p->level, p->id);
  tmp = s->game.map[p->x + p->y * s->x].players;
  while (tmp)
    {
      if (tmp != p)
	sprintf(str, "%s %d", str, tmp->id);
      tmp = tmp->next_t;
    }
  sprintf(str, "%s\n", str);
  communication_sendto(p->client_data, "elevation en cours\n", 0);
  communication_broadcast(s->display_list, str);
  return (1);
}

static void	append_action(t_player *p, t_action *new)
{
  if (p->action_list == NULL)
    {
      p->action_list = new;
      p->action_back = new;
    }
  else
    {
      p->action_back->next = new;
      p->action_back = new;
    }
}

int		new_action(t_server *s, t_player *p, int cmd_idx, char *param)
{
  static char	str[500];
  t_action	*new;

  if (cmd_idx == 9 && handle_incant(s, p) == 0)
    return (0);
  if (cmd_idx == 10)
    {
      memset(str, 0, 500);
      sprintf(str, "pfk %d\n", p->id);
      communication_broadcast(s->display_list, str);
    }
  if ((new = malloc(sizeof(t_action))) == NULL)
    return (1);
  new->cmd_idx = cmd_idx;
  new->player = p;
  new->param = (param ? strdup(param) : param);
  new->next = NULL;
  set_action_time(s, p, &new->time, cmd_idx);
  if (p->busy == 0)
    insert_action_in_queue(s, new);
  else
    append_action(p, new);
  return (0);
}
