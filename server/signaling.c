
#define _XOPEN_SOURCE
#include <signal.h>
#include "server.h"

void	signaling_interrupt(int signum __attribute__((unused)))
{
  g_interrupt = 1;
}

void			signaling_init()
{
  struct sigaction	sa;

  sa.sa_handler = &signaling_interrupt;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, NULL);
}
