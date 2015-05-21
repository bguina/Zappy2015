/*
** server.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:23:42 2012 nathan irjud
** Last update Sun Jul 15 18:20:56 2012 nathan irjud
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"

volatile sig_atomic_t	g_interrupt = 0;

static void	check_eggs(t_server *s, struct timeval *now)
{
  static char	str[500];
  t_egg		*tmp;

  tmp = s->game.eggs;
  while (tmp)
    {
      if (tmp->born == 0 && timercmp(now, &tmp->birth, >))
	{
	  tmp->born = 1;
	  memset(str, 0, 500);
	  sprintf(str, "eht %d\n", tmp->id);
	  communication_broadcast(s->display_list, str);
	  s->teams[tmp->team_idx].egg_slot_nb += 1;
	}
      tmp = tmp->next;
    }
}

static void	set_timeout(t_server *s,
			    struct timeval *now,
			    struct timeval *nextfood,
			    struct timeval *timeout)
{
  if (s->game.actions == NULL || timercmp(nextfood, &s->game.actions->time, <))
    timersub(nextfood, now, timeout);
  else
    timersub(&s->game.actions->time, now, timeout);
}

void		game_shutdown(t_server *s)
{
  communication_end(s);
  fprintf(stderr, "\nInterrupt\n");
  exit(0);
}

static void	replace_last_action(t_server *s, t_action *action,
				    struct timeval *now)
{
  t_action	*next;

  if (action->player->action_list)
    {
      next = action->player->action_list;
      action->player->action_list = next->next;
      next->next = NULL;
      next->time.tv_sec += now->tv_sec;
      next->time.tv_usec += now->tv_usec;
      while (next->time.tv_usec >= 1000000)
	{
	  next->time.tv_usec -= 1000000;
	  next->time.tv_sec += 1;
	}
      insert_action_in_queue(s, next);
    }
  else
    action->player->busy = 0;
  free(action->param);
  free(action);
}

void		do_server_stuff(t_server *s)
{
  struct timeval	now;
  struct timeval	timeout;
  struct timeval	nextfood;
  t_action		*action;

  gettimeofday(&nextfood, NULL);
  while (42)
    {
      if (g_interrupt)
	game_shutdown(s);
      gettimeofday(&now, NULL);
      while (s->game.actions && timercmp(&now, &s->game.actions->time, >))
	{
	  s->commands[s->game.actions->cmd_idx].ptrfunc(s, s->game.actions->player,
							 s->game.actions->param);
	  action = s->game.actions;
	  s->game.actions = s->game.actions->next;
	  replace_last_action(s, action, &now);
	}
      check_eggs(s, &now);
      while (timercmp(&now, &nextfood, >))
	dinner_time(s, &nextfood);
      set_timeout(s, &now, &nextfood, &timeout);
      printf("=======================================- %d - %d\n", s->game.current_food, s->player_nb);
      communication(s, &timeout);
    }
}
