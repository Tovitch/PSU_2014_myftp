/*
** run_serv.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Jul  1 13:46:44 2015 Tony Kruszkewycz
** Last update Thu Jul  9 13:15:47 2015 Tony Kruszkewycz
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<string.h>
#include	"serveur.h"

static void	print_clt_status(t_server *s, int state)
{
  if (state == 0)
    printf(">> Connecté à %s:%hu\n", inet_ntoa(s->clientAddress.sin_addr),
	   ntohs(s->clientAddress.sin_port));
  else
    printf(">> Déconnecté de %s:%hu\n",
	   inet_ntoa(s->clientAddress.sin_addr),
	   ntohs(s->clientAddress.sin_port));
}

static void	delete_cmd_tab(t_com *c)
{
  int		i;

  for (i = 0; c->cmd[i] != NULL; ++i)
    free(c->cmd[i]);
  free(c->cmd);
}

static int	check_cmd_entry(t_com c, t_server *s, int i)
{
  if (i != NB_CMD)
    {
      if ((c.entry[i]->fptr(c, s)) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  else
    {
      if ((dprintf(s->connectSocket, CNF, c.cmd[0])) < 0)
	return (my_perror("dprintf"));
    }
  return (EXIT_SUCCESS);
}

static int	exec_son(t_server *s, t_com c)
{
  int		i;

  bzero(c.msg, sizeof(c.msg));
  while ((read(s->connectSocket, c.msg, MAX_MSG)) > 0)
    {
      if (s->clt_info->logged == 0 && strncasecmp(c.msg, "user", 4) != 0)
      	{
      	  if ((dprintf(s->connectSocket, PLZ_AUTH)) == EXIT_FAILURE)
      	    return (EXIT_FAILURE);
      	}
      else
	{
	  c.msgLength = strlen(c.msg);
	  print_client_entry(&c, s->clt_info);
	  if (!(c.cmd = my_str_to_wordtab(c.msg)))
	    return (EXIT_FAILURE);
	  for (i = 0; i < NB_CMD && strcasecmp(c.cmd[0], c.entry[i]->cmd) != 0;
	       ++i);
	  if ((check_cmd_entry(c, s, i)) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
	  delete_cmd_tab(&c);
	}
      bzero(c.msg, sizeof(c.msg));
    }
  return (xclose(s->connectSocket, EXIT_SUCCESS));
}

int		run_serv(t_server *s, t_com c)
{
  while (1)
    {
      if ((s->connectSocket = accept(s->listenSocket,
				     (struct sockaddr *)&s->clientAddress,
				     &s->clientAddressLen)) == -1)
	return (my_perror("accept"));
      print_clt_status(s, 0);
      if ((fork()) == 0)
	{
	  fill_client(s->clt_info, s->clientAddress);
	  dprintf(s->connectSocket, _220);
	  exec_son(s, c);
	  print_clt_status(s, 1);
	}
      else
	close(s->connectSocket);
    }
  return (EXIT_SUCCESS);
}
