/*
** main.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:22:40 2012 nathan irjud
** Last update Sun Jul 15 17:26:38 2012 nathan irjud
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "server.h"

static void	init_teams(t_server *s, char **team_names)
{
  int		i;

  i = -1;
  s->teams = xmalloc(s->team_nb * sizeof(t_team));
  while (++i < s->team_nb)
    {
      s->teams[i].name = team_names[i];
      s->teams[i].egg_slot_nb = 0;
      s->teams[i].member_nb = 0;
    }
  free(team_names);
}

static int	inner_parse(t_server *s, int *last_opt,
			    int opt, char ***team_names)
{
  *last_opt = (opt == 1 ? *last_opt : opt);
  if (opt == 'p')
    s->port = atoi(optarg);
  else if (opt == 'x')
    s->x = atoi(optarg);
  else if (opt == 'y')
    s->y = atoi(optarg);
  else if (opt == 1 && *last_opt == 'n')
    {
      *team_names = xrealloc(*team_names, (s->team_nb + 2) * sizeof(char *));
      (*team_names)[s->team_nb] = strndup(optarg, TEAM_NAME_SIZE);
      s->team_nb += 1;
      (*team_names)[s->team_nb] = NULL;
    }
  else if (opt == 'c')
    s->team_size = atoi(optarg);
  else if (opt == 't')
    s->f = atoi(optarg);
  else if (opt != 'n')
    {
      write(2, USAGE1, strlen(USAGE1));
      write(2, USAGE2, strlen(USAGE2));
      return (1);
    }
  return (0);
}

static int	check_param(t_server *s)
{
  if (s->x < P_MIN_SIZE || s->x > P_MAX_SIZE)
    {
      printf("Largeur invalide, %i <--> %i\n", P_MIN_SIZE, P_MAX_SIZE);
      return (0);
    }
  else if (s->y < P_MIN_SIZE || s->y > P_MAX_SIZE)
    {
      printf("Hauteur invalide, %i <--> %i\n", P_MIN_SIZE, P_MAX_SIZE);
      return (0);
    }
  else if (s->team_nb < P_MIN_TEAM || s->team_nb > P_MAX_TEAM)
    {
      printf("Nombre de team invalide, %i <--> %i\n", P_MIN_TEAM, P_MAX_TEAM);
      return (0);
    }
  else if (s->f < P_MIN_TIME || s->f > P_MAX_TIME)
    {
      printf("Frequence invalide, %i <--> %i\n", P_MIN_TIME, P_MAX_TIME);
      return (0);
    }
  return (1);
}

static int	parse_params(t_server *s, int ac, char **av)
{
  int		opt;
  int		last_opt;
  char		**team_names;

  opterr = 0;
  team_names = NULL;
  s->port = 4242;
  s->x = 20;
  s->y = 20;
  s->team_nb = 0;
  s->team_size = 1;
  s->f = 100;
  while ((opt = getopt(ac, av, "-p:x:y:nc:t:")) != -1)
    if (inner_parse(s, &last_opt, opt, &team_names) == 1)
      return (1);
  if (team_names == NULL || check_param(s) == 0)
    {
      write(2, USAGE1, strlen(USAGE1));
      write(2, USAGE2, strlen(USAGE2));
      return (1);
    }
  init_teams(s, team_names);
  return (0);
}

int		main(int ac, char **av)
{
  t_server	server;

  server.maxfd = sysconf(_SC_OPEN_MAX);
  srand(time(0));
  if (parse_params(&server, ac, av) == 1)
    return (1);
 if (communication_init(&server) == 0)
    {
      printf("com caca\n");
      return (1);
    }
  init_game(&server);
  init_command(&server);
  init_request(&server);
  do_server_stuff(&server);
  return (0);
}
