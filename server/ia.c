/*
** ia.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:22:20 2012 nathan irjud
** Last update Sun Jul 15 17:26:12 2012 nathan irjud
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"

void		connect_nbr(t_server *s, t_player *p, char *param)
{
  static char	str[500];
  int		slots;

  (void)param;
  slots = s->team_size + s->teams[p->team_idx].egg_slot_nb -
    s->teams[p->team_idx].member_nb;
  memset(str, 0, 500);
  sprintf(str, "%d\n", (slots >= 0 ? slots : 0));
  communication_sendto(p->client_data, str, 1);
}

static void	broadcast_to_display(t_server *s, t_player *p, char *param)
{
  static char	str[500];
  t_client	*tmp;

  tmp = s->display_list;
  memset(str, 0, 500);
  sprintf(str, "pbc %d ", p->id);
  while (tmp)
    {
      communication_sendto(tmp, str, 0);
      communication_sendto(tmp, param, 0);
      communication_sendto(tmp, "\n", 0);
      tmp = tmp->next;
    }
}

void		broadcast(t_server *s, t_player *p, char *param)
{
  static char	str[500];
  t_client	*tmp;

  tmp = s->player_list;
  while (tmp)
    {
      if (tmp != p->client_data)
	{
	  memset(str, 0, 500);
	  sprintf(str, "message %d,", get_dir(s, tmp->player_data, p->x, p->y));
	  communication_sendto(tmp, str, 0);
	  communication_sendto(tmp, param, 0);
	  communication_sendto(tmp, "\n", 0);
	}
      tmp = tmp->next;
    }
  broadcast_to_display(s, p, param);
  communication_sendto(p->client_data, "ok\n", 1);
}

void		lay_egg(t_server *s, t_player *p, char *param)
{
  static int	id = 0;
  static char	str[500];
  t_egg		*new;

  (void)param;
  if ((new = malloc(sizeof(t_egg))) == NULL)
    return;
  new->id = id++;
  new->team_idx = p->team_idx;
  new->x = p->x;
  new->y = p->y;
  new->born = 0;
  new->food = 10;
  new->next = s->game.eggs;
  s->game.eggs = new;
  gettimeofday(&new->birth, NULL);
  new->birth.tv_sec += (600 * 1000000 / s->f) / 1000000;
  new->birth.tv_usec += (600 * 1000000 / s->f) % 1000000;
  communication_sendto(p->client_data, "ok\n", 1);
  memset(str, 0, 500);
  sprintf(str, "enw %d %d %d %d\n", new->id, p->id, p->x, p->y);
  communication_broadcast(s->display_list, str);
}
