/*
** srv_auth.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Jul  1 11:54:12 2015 Tony Kruszkewycz
** Last update Mon Jul  6 16:22:30 2015 Tony Kruszkewycz
*/

#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"serveur.h"

void		fill_client(t_client *client,
			    struct sockaddr_in clientAddress)
{
  client->logged = 0;
  client->nickname = NULL;
  client->clientAddress = clientAddress;
}

void		get_password(t_com c, t_server *s)
{
  (void)c;
  if ((dprintf(s->connectSocket, _230)) == -1)
    return ;
}

int		authentication(t_com c, t_server *s)
{
  char		msg[MAX_MSG + 1];

  bzero(msg, MAX_MSG);
  if (c.cmd[1] && strncmp(c.cmd[1], "Anonymous", strlen("Anonymous")) == 0)
    {
      if ((dprintf(s->connectSocket, _331)) == -1)
	return (EXIT_FAILURE);
      s->clt_info->nickname = strdup(c.cmd[1]);
      s->clt_info->logged = 1;
      get_password(c, s);
    }
  else
    {
      if ((xwrite(s->connectSocket, "Login inconnu.\n", 15)) == -1)
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
