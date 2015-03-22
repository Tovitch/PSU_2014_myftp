/*
** client.c for myftp in /home/kruszk_t/rendu/TPs/tp_myftp/tests
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Sun Mar 15 15:20:49 2015 kruszk_t
** Last update Sun Mar 22 23:08:48 2015 kruszk_t
*/

#include		<stdlib.h>
#include		<unistd.h>
#include		<stdio.h>
#include		<string.h>
#include		<netdb.h>
#include		<netinet/in.h>

#define			MAX_MSG 80
#define			str(x) # x
#define			xstr(x) str(x)

int			init_client(char *host, char *serverPort)
{
  struct addrinfo	hints;
  struct addrinfo	*servinfo;
  int			status;
  int			socketDescriptor;

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  if ((status = getaddrinfo(host, serverPort, &hints, &servinfo)) != 0)
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
      return (EXIT_FAILURE);
    }
  if ((socketDescriptor = socket(servinfo->ai_family,
				 servinfo->ai_socktype,
				 servinfo->ai_protocol)) == -1)
    {
      perror("socket");
      return (EXIT_FAILURE);
    }
  if ((connect(socketDescriptor, servinfo->ai_addr,
	       servinfo->ai_addrlen)) == -1)
    {
      close(socketDescriptor);
      perror("connect");
      return (EXIT_FAILURE);
    }
  freeaddrinfo(servinfo);
  return (socketDescriptor);
}

int			authentication(int socketDescriptor)
{
  char			msg[MAX_MSG + 1];
  char			rcvMsg[MAX_MSG + 1];
  int			msgLen;

  puts("Veuillez vous authentifier :");
  write(1, ">> ", 3);
  memset(msg, 0, sizeof(msg));
  scanf(" %"xstr(MAX_MSG)"[^\n]%*c", msg);
  while (strcmp(msg, "."))
    {
      if ((msgLen = strlen(msg)) > 0)
	{
	  if ((write(socketDescriptor, &msg, msgLen)) == -1)
	    {
	      perror("write");
	      close(socketDescriptor);
	      return (EXIT_FAILURE);
	    }
	  memset(rcvMsg, 0, sizeof(rcvMsg));
	  if ((read(socketDescriptor, &rcvMsg, MAX_MSG)) == -1)
	    {
	      perror("read");
	      close(socketDescriptor);
	      return (EXIT_FAILURE);
	    }
	  printf("	--> %s\n", rcvMsg);
	  if (strncmp(rcvMsg, "Bienvenue", 9) == 0)
	    break;
	}
      memset(msg, 0, sizeof(msg));
      write(1, ">> ", 3);
      scanf(" %"xstr(MAX_MSG)"[^\n]%*c", msg);
    }
  return (EXIT_SUCCESS);
}

int			talker(int socketDescriptor)
{
  fd_set		readSet;
  struct timeval	timeVal;
  char			msg[MAX_MSG];
  int			msgLen;

  if ((authentication(socketDescriptor)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  write(1, ">> Connecté !\n", 15);
  write(1, ">> ", 3);
  memset(msg, 0, sizeof(msg));
  scanf(" %"xstr(MAX_MSG)"[^\n]%*c", msg);
  while (strcmp(msg, "."))
    {
      msgLen = strlen(msg);
      if (msgLen > 0)
	{
	  if (strncmp(msg, "get", 3) == 0)
	    {
	      strcat(msg, " ");
	      strcat(msg, getcwd(NULL, 0));
	    }
	  if ((write(socketDescriptor, &msg, msgLen + 1)) == -1)
	    {
	      perror("write");
	      close(socketDescriptor);
	      return (EXIT_FAILURE);
	    }
	  FD_ZERO(&readSet);
	  FD_SET(socketDescriptor, &readSet);
	  timeVal.tv_sec = 0;
	  timeVal.tv_usec = 25000;
	  memset(msg, 0, sizeof(msg));
	  while (select(socketDescriptor + 1, &readSet, NULL, NULL, &timeVal))
	    {
	      if ((read(socketDescriptor, &msg, MAX_MSG)) == -1)
		{
		  perror("read");
		  close(socketDescriptor);
		  return (EXIT_FAILURE);
		}
	      msgLen = strlen(msg);
	      write(1, &msg, MAX_MSG);
	      memset(msg, 0, sizeof(msg));
	    }
	}
      write(1, ">> ", 3);
      memset(msg, 0, sizeof(msg));
      scanf(" %"xstr(MAX_MSG)"[^\n]%*c", msg);
    }
  return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
  int			socketDescriptor;

  if (ac != 3)
    {
      fprintf(stderr, "Usage: ./%s machine port\n", av[0]);
      return (EXIT_FAILURE);
    }
  if ((socketDescriptor = init_client(av[1], av[2])) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if ((talker(socketDescriptor)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  close(socketDescriptor);
  return (EXIT_SUCCESS);
}
