
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

char			communication_init(t_server *server)
{
  struct sockaddr_in	sin;

  signaling_init();
  if (sprintf(server->welcome_fmt, WELCOME_FMT, server->x, server->y) < 1)
    return (0);
  server->co_nb = 0;
  server->player_nb = 0;
  server->player_list = NULL;
  server->display_list = NULL;
  server->newcomer_list = NULL;
  if ((server->co_nb_max = MY_MIN(FD_SETSIZE, sysconf(_SC_OPEN_MAX)) - 5) < 1
      || (server->sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0
      )
    return (0);
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(server->port);
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(server->sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0
      || listen(server->sockfd, CLIENT_IN_MAX) < 0)
    return (0);
  return (1);
}

void			communication_end(t_server *s)
{
  t_client		*tmp;

  tmp = s->newcomer_list;
  while (tmp != NULL)
    {
      client_shutdown(s, tmp);
      tmp = tmp->next;
    }
  tmp = s->player_list;
  while (tmp != NULL)
    {
      client_shutdown(s, tmp);
      tmp = tmp->next;
    }
  tmp = s->display_list;
  while (tmp != NULL)
    {
      client_shutdown(s, tmp);
      tmp = tmp->next;
    }
  close(s->sockfd);
}
