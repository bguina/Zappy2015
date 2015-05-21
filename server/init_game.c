/*
** init_game.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:22:32 2012 nathan irjud
** Last update Sun Jul 15 17:26:24 2012 nathan irjud
*/

#include <string.h>

#include "server.h"

void		init_game(t_server *s)
{
  memset(&s->game, 0, sizeof(t_game));
  s->game.map = xmalloc(s->x * s->y * sizeof(t_tile));
  memset(s->game.map, 0, s->x * s->y * sizeof(t_tile));
  s->game.players = xmalloc(s->maxfd * sizeof(t_player *));
  memset(s->game.players, 0, s->maxfd * sizeof(t_player *));
  gen_rsc(s, LINEMATE, G_LINEMATE * s->team_nb * ((s->x * s->y / 50) + 1));
  gen_rsc(s, DERAUMERE, G_DERAUMERE * s->team_nb * ((s->x * s->y / 50) + 1));
  gen_rsc(s, SIBUR, G_SIBUR * s->team_nb * ((s->x * s->y / 50) + 1));
  gen_rsc(s, MENDIANE, G_MENDIANE * s->team_nb * ((s->x * s->y / 50) + 1));
  gen_rsc(s, PHIRAS, G_PHIRAS * s->team_nb * ((s->x * s->y / 50) + 1));
  gen_rsc(s, THYSTAME, G_THYSTAME * s->team_nb * ((s->x * s->y / 50) + 1));
}

