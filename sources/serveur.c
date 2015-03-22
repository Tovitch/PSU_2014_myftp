/*
** serveur.c for myftp in /home/kruszk_t/rendu/TPs/tp_myftp/tests
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Sat Mar 14 10:48:10 2015 kruszk_t
** Last update Sun Mar 22 23:11:08 2015 kruszk_t
*/

#include		<stdlib.h>
#include		<stdio.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netdb.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		<string.h>
#include		<unistd.h>
#include		"serveur.h"

void			fill_hints(struct addrinfo *hints)
{
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
}

int			init_serv(t_server *s)
{
  struct addrinfo	hints;
  struct addrinfo	*servinfo;
  int			status;

  fill_hints(&hints);
  if ((status = getaddrinfo(NULL, s->listenPort, &hints, &servinfo)) != 0)
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
      return (EXIT_FAILURE);
    }
  if ((s->listenSocket = socket(servinfo->ai_family, servinfo->ai_socktype,
				servinfo->ai_protocol)) == -1)
    {
      perror("socket");
      return (EXIT_FAILURE);
    }
  if ((bind(s->listenSocket, servinfo->ai_addr, servinfo->ai_addrlen)) == -1)
    {
      close(s->listenSocket);
      perror("bind");
      return (EXIT_FAILURE);
    }
  freeaddrinfo(servinfo);
  return (EXIT_SUCCESS);
}

void			fill_client(t_client *client,
				    struct sockaddr_in clientAddress)
{
  client->logged = 0;
  client->nickname = NULL;
  memset(client->password, 0, sizeof(client->password));
  client->clientAddress = clientAddress;
}

int			authentication(int connectSocket, t_client *client)
{
  char			msg[MAX_MSG + 1];
  int			msgLen;

  while (client->logged == 0)
    {
      memset(msg, 0, sizeof(msg));
      while ((read(connectSocket, &msg, MAX_MSG)) > 0)
	{
	  msgLen = strlen(msg);
	  if (msgLen > 0)
	    {
	      if ((strcmp(msg, "Anonymous")) == 0)
		{
		  client->nickname = strdup(msg);
		  client->logged = 1;
		  if ((write(connectSocket, "Bienvenue ", 10)) == -1 ||
		      (write(connectSocket, &msg, msgLen)) == -1)
		    {
		      perror("write");
		      close(connectSocket);
		      return (EXIT_FAILURE);
		    }
		  break;
		}
	      else
		{
		  if ((write(connectSocket, "Login inconnu.\n", 15)) == -1)
		    {
		      perror("write");
		      close(connectSocket);
		      return (EXIT_FAILURE);
		    }
		}
	      memset(msg, 0, sizeof(msg));
	    }
	}
    }
  return (EXIT_SUCCESS);
}

t_entry			**init_entry(void)
{
  static char		*cmds[] = {"user", "ls", "cd", "get", "put", "pwd",
				   "quit", NULL};
  static int		(*fptrtab[])(t_communication, t_server *) = {cmd_user,
								     cmd_ls,
								     cmd_cd,
								     cmd_get,
								     cmd_put,
								     cmd_pwd,
								     cmd_quit,
								     NULL};
  t_entry		**entry;
  int			i;

  if (!(entry = malloc(sizeof(t_entry *) * NB_CMD + 1)))
    return (NULL);
  for (i = 0; i < NB_CMD; ++i)
    {
      if (!(entry[i] = malloc(sizeof(t_entry))))
	return (NULL);
      memset(entry[i]->cmd, 0, sizeof(entry[i]->cmd));
      strcpy(entry[i]->cmd, cmds[i]);
      entry[i]->fptr = fptrtab[i];
    }
  return (entry);
}

int			serv_listen(t_server *s)
{
  t_communication	c;
  pid_t			pid;
  t_client		clientInfo;
  int			i;

  s->clientAddressLen = sizeof(s->clientAddress);
  if (!(c.entry = init_entry()))
    return (EXIT_FAILURE);
  if ((listen(s->listenSocket, BACKLOG)) == -1)
    {
      perror("listen");
      close(s->listenSocket);
      return (EXIT_FAILURE);
    }
  printf("Attente de connexion TCP sur le port %s\n", s->listenPort);
  while (1)
    {
      if ((s->connectSocket = accept(s->listenSocket,
				     (struct sockaddr *)&s->clientAddress,
				     &s->clientAddressLen)) == -1)
	{
	  perror("accept");
	  close(s->listenSocket);
	  return (EXIT_FAILURE);
	}
      printf(">> Connecté à %s", inet_ntoa(s->clientAddress.sin_addr));
      printf(":%hu\n", ntohs(s->clientAddress.sin_port));
      if ((pid = fork()) == 0)
	{
	  fill_client(&clientInfo, s->clientAddress);
	  if ((authentication(s->connectSocket, &clientInfo)) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
	  memset(c.msg, 0, sizeof(c.msg));
	  while ((read(s->connectSocket, &c.msg, MAX_MSG)) > 0)
	    {
	      c.msgLength = strlen(c.msg);
	      if (c.msgLength > 0)
		{
		  printf("	-->  %s\n", c.msg);
		  if (!(c.cmd = my_str_to_wordtab(c.msg)))
		    return (EXIT_FAILURE);
		  for (i = 0; i < NB_CMD &&
			 strcmp(c.cmd[0], c.entry[i]->cmd) != 0; ++i);
		  if (i != NB_CMD)
		    {
		      if ((c.entry[i]->fptr(c, s)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		    }
		  else
		    {
		      write(s->connectSocket, c.cmd[0], strlen(c.cmd[0]));
		      write(s->connectSocket, ": commande introuvable\n", 23);
		    }
		  for (i = 0; c.cmd[i] != NULL; ++i)
		    free(c.cmd[i]);
		  free(c.cmd);
		  memset(c.msg, 0, sizeof(c.msg));
		}
	    }
	}
      else
	close(s->connectSocket);
    }
  return (EXIT_SUCCESS);
}

char			*my_strdup(char *str)
{
  char			*ret;
  int			i;

  if (!(ret = malloc(sizeof(char) * strlen(str) + 1)))
    return (NULL);
  for (i = 0; str[i]; ++i)
    ret[i] = str[i];
  return (ret);
}

int			main(int ac, char **av)
{
  t_server		server;

  if (ac != 2)
    {
      fprintf(stderr, "Usage: ./%s port\n", av[0]);
      return (EXIT_FAILURE);
    }
  server.root = getcwd(NULL, 0);
  server.path = my_strdup("/");
  server.listenPort = av[1];
  if (init_serv(&server) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (serv_listen(&server) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  close(server.listenSocket);
  return (EXIT_SUCCESS);
}
