
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"

static char	client_msg_get(t_client *c, char *request)
{
  char		*cursor;
  char		*rcursor;
  t_msg		*tmp;
  int		len;

  memset(request, '\0', c->in_buf_nb * IN_BUFSIZE + 1);
  tmp = c->in_buf_list;
  cursor = request;
  while (tmp->next != NULL)
    {
      len = IN_BUFSIZE - tmp->delta;
      cursor = memcpy(cursor, tmp->buf + tmp->delta, len) + len;
      tmp = tmp->next;
    }
  *cursor = '\0';
  rcursor = tmp->buf + tmp->delta;
  len = (char *)rawmemchr(rcursor, '\n') - rcursor;
  *(rcursor + len) = '\0';
  tmp->delta += len + 1;
  if ((int)strlen(request) > (c->in_buf_nb - 1) * IN_BUFSIZE
      || (int)strlen(rcursor) != len)
    {
      puts("========\nprocessing error report:");
      printf("strlen(request)=> %lu <= (c->in_buf_nb - 1) * IN_BUFSIZE=> %i\nstrlen(rcursor)=> %lu == len=> %i\n",
	     strlen(request), (c->in_buf_nb - 1) * IN_BUFSIZE, strlen(rcursor), len);
      return (0);
    }
  strcpy(cursor, rcursor);
  return (1);
}

t_msg		*client_msg_init(int buf_size)
{
  t_msg		*ret;

  if ((ret = malloc(sizeof(*ret))) == NULL
      || (ret->buf = malloc(buf_size + 1)) == NULL)
    {
      free(ret);
      return (NULL);
    }
  ret->buf_size = buf_size;
  ret->cursor = 0;
  ret->delta = 0;
  ret->next = NULL;
  return (ret);
}

char		client_msg_process(t_server *s, t_client *c)
{
  char		*request;
  char		ret;

  if ((request = malloc(c->in_buf_nb * IN_BUFSIZE + 1)) == NULL)
    return (1);
  else if (!client_msg_get(c, request) && printf("processing error\n"))
    return (0);
  while (c->in_buf_list->next != NULL)
    client_msg_prepop(&c->in_buf_list);
  c->in_buf_nb = 1;
  ret = 1;
  printf("debugaretirer[n.%i]> %s\n", c->fd, request);
  if (c->in_pend_msg_nb < 0)
    {
      if (!(ret = crequest_newcomer(s, c, request)))
	send(c->fd, RESP_KO, 0);
    }
  else if (c->in_pend_msg_nb < MSG_IN_MAX)
    ret = crequest_oldfag(s, c, request);
  else
    puts("too much requests for this client, ignored\n");
  free(request);
  return (ret);
}

t_msg		*client_msg_prepop(t_msg **msglist)
{
  t_msg		*ret;

  if (*msglist == NULL)
    return (NULL);
  ret = (*msglist)->next;
  free((*msglist)->buf);
  free(*msglist);
  *msglist = ret;
  return (ret);
}

t_msg		*client_msg_read_slot(t_client *c)
{
  t_msg		*tail;
  t_msg		*new;

  if ((tail = c->ibl_back) == NULL || tail->cursor >= tail->buf_size)
    {
      if ((new = client_msg_init(IN_BUFSIZE)) == NULL)
	return (NULL);
      if (tail != NULL)
	tail->next = new;
      else
	c->in_buf_list = new;
      c->ibl_back = new;
      c->in_buf_nb++;
    }
  return (c->ibl_back);
}
