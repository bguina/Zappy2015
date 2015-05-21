/*
** game_requests.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:22:12 2012 nathan irjud
** Last update Sun Jul 15 17:26:06 2012 nathan irjud
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

void		msz(t_server *s, t_client *c, int param1, int param2)
{
  static char	str[500];

  (void)param1;
  (void)param2;
  memset(str, 0, 500);
  sprintf(str, "msz %d %d\n", s->x, s->y);
  communication_sendto(c, str, 0);
}

void		bct(t_server *s, t_client *c, int param1, int param2)
{
  static char	str[500];
  int		i;

  if (param1 >= s->x || param2 >= s->y || param1 < 0 || param2 < 0)
    communication_sendto(c, BAD_PARAM, 0);
  else
    {
      memset(str, 0, 500);
      i = -1;
      sprintf(str, "bct %d %d", param1, param2);
      while (++i < NB_OBJECTS)
	sprintf(str, "%s %d", str, s->game.map[param1 + param2 * s->x].objects[i]);
      sprintf(str, "%s\n", str);
      communication_sendto(c, str, 0);
    }
}

void		mct(t_server *s, t_client *c, int param1, int param2)
{
  int		i;
  int		j;

  (void)param1;
  (void)param2;
  i = -1;
  while (++i < s->x)
    {
      j = -1;
      while (++j < s->y)
	bct(s, c, i, j);
    }
}

void		tna(t_server *s, t_client *c, int param1, int param2)
{
  static char	str[500];
  int		i;

  (void)param1;
  (void)param2;
  i = -1;
  while (++i < s->team_nb)
    {
      memset(str, 0, 500);
      sprintf(str, "tna %s\n", s->teams[i].name);
      communication_sendto(c, str, 0);
    }
}

void		sgt(t_server *s, t_client *c, int param1, int param2)
{
  static char	str[500];

  (void)param1;
  (void)param2;
  memset(str, 0, 500);
  sprintf(str, "sgt %d\n", s->f);
  communication_sendto(c, str, 0);
}
