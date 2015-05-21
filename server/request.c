/*
** request.c for zappy in /home/irjud_n//tek2/UNIX/zappy/zappy-2015-2014s-irjud_n/server
** 
** Made by nathan irjud
** Login   <irjud_n@epitech.net>
** 
** Started on  Sun Jul 15 17:23:37 2012 nathan irjud
** Last update Sun Jul 15 17:30:55 2012 nathan irjud
*/

#include <string.h>

#include "server.h"

void		init_request(t_server *s)
{
  memset(s->requests, 0, NB_REQUESTS * sizeof(t_request));

  strcpy(s->requests[0].name, "msz");
  s->requests[0].ptrfunc = msz;
  strcpy(s->requests[1].name, "bct");
  s->requests[1].ptrfunc = bct;
  strcpy(s->requests[2].name, "mct");
  s->requests[2].ptrfunc = mct;
  strcpy(s->requests[3].name, "tna");
  s->requests[3].ptrfunc = tna;
  strcpy(s->requests[4].name, "ppo");
  s->requests[4].ptrfunc = ppo;
  strcpy(s->requests[5].name, "plv");
  s->requests[5].ptrfunc = plv;
  strcpy(s->requests[6].name, "pin");
  s->requests[6].ptrfunc = pin;
  strcpy(s->requests[7].name, "sgt");
  s->requests[7].ptrfunc = sgt;
  strcpy(s->requests[8].name, "sst");
  s->requests[8].ptrfunc = sst;
}

void		request_broadcast(t_server *s,
				  void (*ptrfunc)(t_server *, t_client *, int, int),
				  int param1, int param2)
{
  t_client	*tmp;

  tmp = s->display_list;
  while (tmp)
    {
      if (tmp->fd > -1)
	ptrfunc(s, tmp, param1, param2);
      tmp = tmp->next;
    }
}

void		new_graphic_info(t_server *s, t_client *c)
{
  t_client	*tmp;

  msz(s, c, 0, 0);
  sgt(s, c, 0, 0);
  mct(s, c, 0, 0);
  tna(s, c, 0, 0);
  tmp = s->player_list;
  while (tmp)
    {
      pnw(s, c, tmp->player_data->id, 0);
      pin(s, c, tmp->player_data->id, 0);
      tmp = tmp->next;
    }
}
