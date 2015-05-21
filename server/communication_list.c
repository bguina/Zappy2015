
#define _GNU_SOURCE
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "server.h"

int			list_fdset(t_client **lbeg,
				   t_server *sdata,
				   fd_set *rfds,
				   fd_set *wfds)
{
  t_client		*l;
  t_client		*save;
  int			nfds;

  nfds = 0;
  l = *lbeg;
  save = NULL;
  while (l != NULL)
    if (l->fd > -1)
      {
	if (!l->must_die)
	  FD_SET(l->fd, rfds);
	else if (l->out_msg_list == NULL)
	  client_shutdown(sdata, l);
	if (l->out_msg_list != NULL)
	  FD_SET(l->fd, wfds);
	if (!l->must_die || l->out_msg_list != NULL)
	  nfds = MY_MAX(l->fd, nfds);
	save = l;
	l = l->next;
      }
    else
      l = client_discard(l, sdata, lbeg, save);
  return (nfds);
}

static t_msg		*list_write_next(t_client *c, char *cont)
{
  t_msg			*msg;

  msg = c->out_msg_list;
  if (msg->next == NULL)
    c->oml_back = NULL;
  c->out_msg_list = msg->next;
  free(msg->buf);
  free(msg);
  *cont = (c->out_msg_list != NULL);
  return (c->out_msg_list);
}

t_client	*list_move(t_client **from, t_client **to, t_client *what)
{
  t_client	*l;

  if (*from == what)
    *from = what->next;
  else
    {
      l = *from;
      while (l != NULL && l->next != what)
	l = l->next;
      if (l == NULL)
	return (NULL);
      l->next = what->next;
    }
  what->next = *to;
  *to = what;
  return (what);
}

void			list_write(t_server *s, t_client *l, fd_set *wfds)
{
  int			ret;
  t_msg			*msg;
  char			dowhile;

  while (l != NULL)
    {
      if ((msg = l->out_msg_list) != NULL && FD_ISSET(l->fd, wfds))
	{
	  dowhile = 1;
	  while (dowhile)
	    {
	      dowhile = 0;
	      errno = 0;
	      if ((ret = send(l->fd, msg->buf + msg->cursor,
			      msg->buf_size - msg->cursor, MSG_NOSIGNAL)) > -1)
		{
		  if ((msg->cursor += ret) >= msg->buf_size)
		    msg = list_write_next(l, &dowhile);
		}
	      else if (errno != EINTR && errno != EWOULDBLOCK && errno != EAGAIN)
		client_shutdown(s, l);
	    }
	}
      l = l->next;
    }
}

void			list_read(t_server *s, t_client *l, fd_set *rfds)
{
  int			ret;
  t_msg			*msg;

  while (l != NULL)
    {
      if (FD_ISSET(l->fd, rfds) && (msg = client_msg_read_slot(l)) != NULL)
	{
	  errno = 0;
	  if ((ret = recv(l->fd, msg->buf + msg->cursor,
			  msg->buf_size - msg->cursor, 0)) > 0)
	    {
	      msg->cursor += ret;
	      while (memchr(msg->buf + msg->delta, '\n',
			    msg->cursor - msg->delta) != NULL)
		if (!client_msg_process(s, l))
		  client_shutdown(s, l);
	      if (msg->delta == msg->buf_size && !(--l->in_buf_nb))
		l->ibl_back = client_msg_prepop(&l->in_buf_list);
	    }
	  else if (errno != EINTR && errno != EWOULDBLOCK && errno != EAGAIN)
	    client_shutdown(s, l);
	}
      l = l->next;
    }
}
