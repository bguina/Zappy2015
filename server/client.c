
#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include "server.h"

void		client_newcomer(t_server *s, int sockfd)
{
  t_client	*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    return;
  new->fd = sockfd;
  new->must_die = 0;
  new->in_pend_msg_nb = -1;
  new->in_buf_nb = 0;
  new->in_buf_list = NULL;
  new->out_msg_list = NULL;
  new->ibl_back = NULL;
  new->oml_back = NULL;
  new->player_data = NULL;
  new->next = s->newcomer_list;
  s->newcomer_list = new;
  s->co_nb++;
  communication_sendto(new, WELCOME, 0);
}

void		client_shutdown(t_server *s, t_client *c)
{
  if (c->fd < 0)
    return;
  if (c->player_data != NULL)
    player_dc(s, c);
  shutdown(c->fd, SHUT_RDWR);
  close(c->fd);
  c->fd = -1;
  s->co_nb--;
}

t_client	*client_discard(t_client *c,
				t_server *s,
				t_client **lbeg,
				t_client *save)
{
  t_client	*next;

  s->co_nb--;
  if (*lbeg == s->player_list)
    s->player_nb--;
  while ((client_msg_prepop(&c->in_buf_list)) != NULL);
  while ((client_msg_prepop(&c->out_msg_list)) != NULL);
  next = c->next;
  if (save == NULL)
    *lbeg = next;
  else
    save->next = next;
  free(c);
  return (next);
}
