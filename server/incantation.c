/*
** incantation.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:22:27 2012 nathan irjud
** Last update Sun Jul 15 17:26:16 2012 nathan irjud
*/

#include <stdio.h>
#include <string.h>

#include "server.h"

static int	check_stones(t_server *s, t_player *p, char *stones)
{
  int		i;

  i = 0;
  while (++i < NB_OBJECTS)
    if (s->game.map[p->x + p->y * s->y].objects[i] != stones[i] - '0')
      return (0);
  return (1);
}

int		incantation_valide(t_server *s, t_player *p)
{
  t_player	*tmp;
  int		count;

  count = 0;
  tmp = s->game.map[p->x + p->y * s->x].players;
  while (tmp)
    {
      if (tmp->level != p->level)
	return (0);
      count++;
      tmp = tmp->next_t;
    }
  if ((p->level == 1 && count == 1 && check_stones(s, p, S_LEVEL1))
      || (p->level == 2 && count == 2 && check_stones(s, p, S_LEVEL2))
      || (p->level == 3 && count == 2 && check_stones(s, p, S_LEVEL3))
      || (p->level == 4 && count == 4 && check_stones(s, p, S_LEVEL4))
      || (p->level == 5 && count == 4 && check_stones(s, p, S_LEVEL5))
      || (p->level == 6 && count == 6 && check_stones(s, p, S_LEVEL6))
      || (p->level == 7 && count == 6 && check_stones(s, p, S_LEVEL7)))
    return (1);
  return (0);
}

void		incantation(t_server *s, t_player *p, char *param)
{
  static char	str[500];
  t_player	*tmp;
  int		success;

  (void)param;
  memset(str, 0, 500);
  if ((success = incantation_valide(s, p)) == 1)
    {
      sprintf(str, "niveau actuel : %d\n", p->level + 1);
      tmp = s->game.map[p->x + p->y * s->x].players;
      while (tmp)
	{
	  communication_sendto(tmp->client_data, str, (tmp == p ? 1 : 0));
	  tmp->level += 1;
	  request_broadcast(s, plv, p->id, 0);
	  tmp = tmp->next_t;
	}
    }
  else
    communication_sendto(p->client_data, "ko\n", 1);
  memset(str, 0, 500);
  sprintf(str, "pie %d %d %d\n", p->x, p->y, success);
  communication_broadcast(s->display_list, str);
}
