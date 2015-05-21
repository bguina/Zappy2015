
#define _GNU_SOURCE
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "server.h"

static void		communication_do_transfer(t_server *server,
						  fd_set *rfds,
						  fd_set *wfds)
{
  int			ret;
  struct sockaddr_in	sin;
  unsigned int		sinlen;

  list_write(server, server->newcomer_list, wfds);
  list_write(server, server->display_list, wfds);
  list_write(server, server->player_list, wfds);
  list_read(server, server->player_list, rfds);
  list_read(server, server->display_list, rfds);
  list_read(server, server->newcomer_list, rfds);
  if (FD_ISSET(server->sockfd, rfds))
    {
      memset(&sin, 0, (sinlen = sizeof(sin)));
      errno = 0;
      if ((ret = accept4(server->sockfd,
			 (struct sockaddr *)&sin,
			 &sinlen,
			 SOCK_NONBLOCK)) > -1)
	client_newcomer(server, ret);
    }
}

char			communication(t_server *server,
				      struct timeval *timeout)
{
  fd_set		rfds;
  fd_set		wfds;
  int			nfds;
  int			ret;

  FD_ZERO(&rfds);
  FD_ZERO(&wfds);
  nfds = 0;
  if (server->co_nb < server->co_nb_max)
    {
      nfds = server->sockfd;
      FD_SET(nfds, &rfds);
    }
  nfds = MY_MAX(nfds, list_fdset(&server->player_list, server, &rfds, &wfds));
  nfds = MY_MAX(nfds, list_fdset(&server->display_list, server, &rfds, &wfds));
  nfds = MY_MAX(nfds, list_fdset(&server->newcomer_list, server, &rfds, &wfds));
  errno = 0;
  if ((ret = select(nfds + 1, &rfds, &wfds, NULL, timeout)) < 1)
    return (!ret || errno == EINTR);
  communication_do_transfer(server, &rfds, &wfds);
  return (1);
}

char		communication_sendto(t_client *c,
				     char *message,
				     char action_end)
{
  t_msg		*new;

  if (c != NULL && !c->must_die)
    {
      if ((new = client_msg_init(strlen(message))) == NULL)
	return (0);
      strcpy(new->buf, message);
      if (c->oml_back != NULL)
	c->oml_back->next = new;
      else
	c->out_msg_list = new;
      c->oml_back = new;
      if (action_end && c->in_pend_msg_nb > 0)
	c->in_pend_msg_nb--;
    }
  return (1);
}

char		communication_broadcast(t_client *l, char *message)
{
  char		ret;

  ret = 0;
   while (l != NULL)
    {
      if (l->fd > -1 && !communication_sendto(l, message, 0))
	ret++;
      l = l->next;
    }
  return (ret);
}
