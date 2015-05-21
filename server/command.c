/*
** command.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:21:34 2012 nathan irjud
** Last update Sun Jul 15 17:24:53 2012 nathan irjud
*/

#include <string.h>

#include "server.h"

static void	init_first_half(t_server *s)
{
  strcpy(s->commands[0].name, "avance");
  s->commands[0].nb_cycle = 7;
  s->commands[0].ptrfunc = avance;
  strcpy(s->commands[1].name, "droite");
  s->commands[1].nb_cycle = 7;
  s->commands[1].ptrfunc = droite;
  strcpy(s->commands[2].name, "gauche");
  s->commands[2].nb_cycle = 7;
  s->commands[2].ptrfunc = gauche;
  strcpy(s->commands[3].name, "voir");
  s->commands[3].nb_cycle = 7;
  s->commands[3].ptrfunc = voir;
  strcpy(s->commands[4].name, "inventaire");
  s->commands[4].nb_cycle = 1;
  s->commands[4].ptrfunc = inventaire;
  strcpy(s->commands[5].name, "prend");
  s->commands[5].nb_cycle = 7;
  s->commands[5].ptrfunc = prend;
}

static void	init_second_half(t_server *s)
{
  strcpy(s->commands[6].name, "pose");
  s->commands[6].nb_cycle = 7;
  s->commands[6].ptrfunc = pose;
  strcpy(s->commands[7].name, "expluse");
  s->commands[7].nb_cycle = 7;
  s->commands[7].ptrfunc = expulse;
  strcpy(s->commands[8].name, "broadcast");
  s->commands[8].nb_cycle = 7;
  s->commands[8].ptrfunc = broadcast;
  strcpy(s->commands[9].name, "incantation");
  s->commands[9].nb_cycle = 300;
  s->commands[9].ptrfunc = incantation;
  strcpy(s->commands[10].name, "fork");
  s->commands[10].nb_cycle = 42;
  s->commands[10].ptrfunc = lay_egg;
  strcpy(s->commands[11].name, "connect_nbr");
  s->commands[11].nb_cycle = 0;
  s->commands[11].ptrfunc = connect_nbr;
}

void		init_command(t_server *s)
{
  memset(s->commands, 0, NB_COMMANDS * sizeof(t_command));
  init_first_half(s);
  init_second_half(s);
}
