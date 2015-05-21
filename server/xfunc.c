/*
** xalloc.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sat Jul  7 19:03:09 2012 nathan irjud
** Last update Sun Jul 15 17:30:15 2012 nathan irjud
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

void		xwrite(int fd, void *buf, int count)
{
  int		ret;

  if ((ret = write(fd, buf, count)) == -1)
    {
      if (write(2, WRITE_ERROR, strlen(WRITE_ERROR)) == -1)
	exit(EXIT_FAILURE);
      exit(EXIT_FAILURE);
    }
}

void		*xmalloc(int size)
{
  void		*ret;

  if ((ret = malloc(size)) == NULL)
    {
      xwrite(2, MALLOC_ERROR, strlen(MALLOC_ERROR));
      exit(EXIT_FAILURE);
    }
  return (ret);
}

void		*xrealloc(void *ptr, int size)
{
  void		*ret;

  if ((ret = realloc(ptr, size)) == NULL)
    {
      xwrite(2, REALLOC_ERROR, strlen(REALLOC_ERROR));
      exit(EXIT_FAILURE);
    }
  return (ret);
}
