/*
** serveur.c for myftp in /home/kruszk_t/rendu/TPs/tp_myftp/tests
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Sat Mar 14 10:48:10 2015 kruszk_t
** Last update Mon Jul  6 12:32:39 2015 Tony Kruszkewycz
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	"serveur.h"

void		print_client_entry(t_com *c, t_client *info)
{
  if (info->nickname)
    printf("\t--> %s: %s\n", info->nickname, c->msg);
  else
    printf("\t--> Unknown: %s\n", c->msg);
}

static void	my_free(t_server *s, t_com *c)
{
  int		i;

  for (i = 0; i < NB_CMD; ++i)
    free(c->entry[i]);
  free(c->entry);
  free(s->clt_info);
}

int		serv_listen(t_server *s)
{
  t_com		c;

  s->clientAddressLen = sizeof(s->clientAddress);
  if (!(c.entry = init_entry()))
    return (EXIT_FAILURE);
  if ((listen(s->listenSocket, BACKLOG)) == -1)
    return (my_perror("listen"));
  printf(WAIT_CO, s->listenPort);
  if ((run_serv(s, c)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  my_free(s, &c);
  return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
  t_server	server;

  if (ac != 2)
    {
      fprintf(stderr, "Usage: %s port\n", av[0]);
      return (EXIT_FAILURE);
    }
  server.root = getcwd(NULL, 0);
  server.path = my_strdup("/");
  server.listenPort = av[1];
  if (init_serv(&server) == EXIT_FAILURE)
    {
      close(server.listenSocket);
      close(server.connectSocket);
      return (EXIT_FAILURE);
    }
  if (serv_listen(&server) == EXIT_FAILURE)
    {
      close(server.connectSocket);
      close(server.listenSocket);
      return (EXIT_FAILURE);
    }
  close(server.listenSocket);
  return (EXIT_SUCCESS);
}
