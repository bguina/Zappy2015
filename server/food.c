/*
** food.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:22:03 2012 nathan irjud
** Last update Sun Jul 15 17:25:53 2012 nathan irjud
*/

#include "server.h"

static void	feed_players(t_server *s)
{
  t_client	*tmp_c;

  tmp_c = s->player_list;
  while (tmp_c)
    {
      if (tmp_c->player_data && tmp_c->fd > -1)
	{
	  if (tmp_c->player_data->bag[FOOD] == 0)
	    player_death(s, tmp_c->player_data);
	  else
	    tmp_c->player_data->bag[FOOD] -= 1;
	}
      tmp_c = tmp_c->next;
    }
}

static void	feed_ghosts(t_server *s)
{
  t_player	*tmp_g;
  t_player	*dead;

  tmp_g = s->game.ghosts;
  while (tmp_g)
    {
      if (tmp_g->bag[FOOD] == 0)
	{
	  dead = tmp_g;
	  tmp_g = tmp_g->next_g;
	  ghost_death(s, dead);
	}
      else
	{
	  tmp_g->bag[FOOD] -= 1;
	  tmp_g = tmp_g->next_g;
	}
    }
}

static void	feed_eggs(t_server *s)
{
  t_egg		*tmp_e;
  t_egg		*dead;

  tmp_e = s->game.eggs;
  while (tmp_e)
    {
      if (tmp_e->food == 0)
	{
	  dead = tmp_e;
	  tmp_e = tmp_e->next;
	  egg_death(s, dead);
	}
      else
	{
	  tmp_e->food -= 1;
	  tmp_e = tmp_e->next;
	}
    }
}

void		dinner_time(t_server *s, struct timeval *next)
{
  int		new_food;

  feed_players(s);
  feed_ghosts(s);
  feed_eggs(s);
  while (next->tv_usec < 0)
    {
      next->tv_usec += 100000;
      next->tv_sec -= 1;
    }
  next->tv_sec += (126 * 1000000 / s->f) / 1000000;
  next->tv_usec += (126 * 1000000 / s->f) % 1000000;
  while (next->tv_usec >= 1000000)
    {
      next->tv_usec -= 1000000;
      next->tv_sec += 1;
    }
  new_food = (s->player_nb * 5 * (s->x * s->y / 10)) - s->game.current_food;
  gen_rsc(s, FOOD, new_food);
  s->game.current_food += new_food;
}

