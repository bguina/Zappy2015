/*
** map_utilities.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:22:58 2012 nathan irjud
** Last update Sun Jul 15 17:26:52 2012 nathan irjud
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "server.h"

t_tile		*get_front_tile(t_server *s, t_player *p)
{
  int		x;
  int		y;

  x = p->x;
  y = p->y;
  if (p->dir == NORTH)
    y = (p->y - 1 + s->y) % s->y;
  else if (p->dir == EAST)
    x = (p->x + 1) % s->x;
  else if (p->dir == SOUTH)
    y = (p->y + 1) % s->y;
  else
    x = (p->x - 1 + s->x) % s->x;
  return (&s->game.map[x + y * s->x]);
}

static int	get_shortest(int p, int s, int xy)
{
  if (abs(p - xy) < s - abs(p - xy))
    return (xy - p);
  else
    return ((p > xy ? ((xy - p) + s) : ((xy - p) - s)));
}

int		get_dir(t_server *s, t_player *p, int x, int y)
{
  int		xy[2];
  double	angle;
  int		dir;

  xy[0] = get_shortest(p->x, s->x, x);
  xy[1] = get_shortest(p->y, s->y, y);
  angle = 2 * atan(xy[1]/(xy[0] + sqrt(xy[0] * xy[0] + xy[1] * xy[1])));
  dir = 0;
  if (angle >= ANGLE2 && angle <= ANGLE3)
    dir = 1;
  else if (angle > ANGLE3 && angle < ANGLE4)
    dir = 2;
  else if (angle >= ANGLE4 || angle <= -ANGLE4)
    dir = 3;
  else if (angle > -ANGLE4 && angle < -ANGLE3)
    dir = 4;
  else if (angle >= -ANGLE3 && angle <= -ANGLE2)
    dir = 5;
  else if (angle > -ANGLE2 && angle < -ANGLE1)
    dir = 6;
  else if (angle >= -ANGLE1 && angle <= ANGLE1)
    dir = 7;
  else if (angle > ANGLE1 && angle < ANGLE2)
    dir = 8;
  return ((dir ? ((dir + (p->dir - 1) * 2 - 1) % 8 + 1) : dir));
}

void		gen_rsc(t_server *s, int idx, int nb)
{
  int		i;
  int		randx;
  int		randy;

  i = -1;
  while (++i < nb)
    {
      randx = rand() % s->x;
      randy = rand() % s->y;
      s->game.map[randx + randy * s->x].objects[idx] += 1;
      request_broadcast(s, bct, randx, randy);
    }

}

void		append_text(char *str, char *str2, int n)
{
  int		i;

  i = -1;
  while (++i < n)
    sprintf(str, "%s%s", str, str2);
}

