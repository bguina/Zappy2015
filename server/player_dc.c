/*
** player_dc.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:23:25 2012 nathan irjud
** Last update Sun Jul 15 17:28:27 2012 nathan irjud
*/

#include "server.h"

void		player_dc(t_server *s, t_client *c)
{
  c->player_data->client_data = NULL;
  c->player_data->next_g = s->game.ghosts;
  s->game.ghosts = c->player_data;
  s->game.players[c->player_data->id] = NULL;
  s->teams[c->player_data->team_idx].member_nb -= 1;
}
