/*
** player_requests.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:23:32 2012 nathan irjud
** Last update Sun Jul 15 17:28:55 2012 nathan irjud
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

void		ppo(t_server *s, t_client *c, int param1, int param2)
{
  static char	str[500];

  (void)param2;
  if (s->game.players[param1] == NULL)
    communication_sendto(c, BAD_PARAM, 0);
  else
    {
      memset(str, 0, 500);
      sprintf(str, "ppo %d %d %d %d\n", param1, s->game.players[param1]->x,
	      s->game.players[param1]->y, s->game.players[param1]->dir);
      communication_sendto(c, str, 0);
    }
}

void		plv(t_server *s, t_client *c, int param1, int param2)
{
  static char	str[500];

  (void)param2;
  if (param1 < 0 || param1 >= s->maxfd || s->game.players[param1] == NULL)
    communication_sendto(c, BAD_PARAM, 0);
  else
    {
      memset(str, 0, 500);
      sprintf(str, "plv %d %d\n", param1, s->game.players[param1]->level);
      communication_sendto(c, str, 0);
    }
}

void		pin(t_server *s, t_client *c, int param1, int param2)
{
  static char	str[500];
  int		i;

  (void)param2;
  if (param1 < 0 || param1 >= s->maxfd || s->game.players[param1] == NULL)
    communication_sendto(c, BAD_PARAM, 0);
  else
    {
      memset(str, 0, 500);
      i = -1;
      sprintf(str, "pin %d %d %d", param1, s->game.players[param1]->x,
	      s->game.players[param1]->y);
      while (++i < NB_OBJECTS)
	sprintf(str, "%s %d", str, s->game.players[param1]->bag[i]);
      sprintf(str, "%s\n", str);
      communication_sendto(c, str, 0);
    }
}

void		pnw(t_server *s, t_client *c, int param1, int param2)
{
  static char	str[500];

  (void)param2;
  memset(str, 0, 500);
  sprintf(str, "pnw %d %d %d %d %d %s\n",
	  param1,
	  s->game.players[param1]->x,
	  s->game.players[param1]->y,
	  s->game.players[param1]->dir,
	  s->game.players[param1]->level,
	  s->teams[s->game.players[param1]->team_idx].name);
  communication_sendto(c, str, 0);
}

void		sst(t_server *s, t_client *c, int param1, int param2)
{
  (void)param2;
  if (param1 > P_MAX_TIME || param1 < P_MIN_TIME)
    communication_sendto(c, BAD_PARAM, 0);
  else
    {
      s->f = param1;
      sgt(s, c, 0, 0);
    }
}
