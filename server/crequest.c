
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

char		crequest_newcomer(t_server *s, t_client *c, char *req)
{
  int		i;
  static char	wstr[WELCOME_BUFSZ];
  int		space_left;

  if (!strcmp(req, IAMDISPLAY))
    {
      list_move(&s->newcomer_list, &s->display_list, c);
      c->in_pend_msg_nb = 0;
      new_graphic_info(s, c);
      return (1);
    }
  i = -1;
  while (++i < s->team_nb && strcmp(s->teams[i].name, req));
  if (i == s->team_nb)
    return (0);
  space_left = s->team_size - s->teams[i].member_nb + s->teams[i].egg_slot_nb;
  if (sprintf(wstr, s->welcome_fmt, space_left) < 1)
    return (0);
  communication_sendto(c, wstr, 0);
  if (space_left < 1 || (c->player_data = malloc(sizeof(t_player))) == NULL)
    return (0);
  c->in_pend_msg_nb = 0;
  s->player_nb++;
  new_player(s, c, i);
  return (list_move(&s->newcomer_list, &s->player_list, c) != NULL);
}

static char	crequest_request(t_server *s, t_client *c, char *req)
{
  int		i;
  char		*tok;
  int		p1;
  int		p2;

  if ((tok = strtok(req, " ")) == NULL)
    return (0);
  i = -1;
  while (++i < NB_REQUESTS && strcmp(s->requests[i].name, tok));
  p1 = -1;
  p2 = -1;
  if ((tok = strtok(NULL, " ")) != NULL)
    p1 = atoi(tok);
  if (tok != NULL && (tok = strtok(NULL, " ")) != NULL)
    p2 = atoi(tok);
  if (i == NB_REQUESTS || p1 < -1 || p2 < -1)
    {
      communication_sendto(c, i == NB_REQUESTS ? "suc\n" : "sbp\n", 0);
      return (1);
    }
  s->requests[i].ptrfunc(s, c, p1, p2);
  return (1);
}

static char	crequest_command(t_server *s, t_client *c, char *req)
{
  int		i;
  char		*tok;

  if ((tok = strtok(req, " ")) == NULL)
    return (0);
  i = -1;
  while (++i < NB_COMMANDS && strcmp(s->commands[i].name, tok));
  if (i == NB_COMMANDS)
    communication_sendto(c, "ko\n", 0);
  else
    if (0 == new_action(s, c->player_data, i, strtok(NULL, "")))
      c->in_pend_msg_nb++;
  return (1);
}

char		crequest_oldfag(t_server *s, t_client *c, char *req)
{
  char		ret;

  ret = 1;
  if (c->player_data == NULL)
    ret = crequest_request(s, c, req);
  else
    ret = crequest_command(s, c, req);
  return (ret);
}
