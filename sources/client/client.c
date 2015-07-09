/*
** client.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Thu Jun 25 15:56:54 2015 Tony Kruszkewycz
** Last update Thu Jul  9 12:58:31 2015 Tony Kruszkewycz
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<string.h>
#include	"client.h"

int		read_stdin(char *msg)
{
  char			*s;
  char			*lf;

  write(1, ">> ", 3);
  bzero(msg, MAX_MSG);
  if (!(s = fgets(msg, MAX_MSG, stdin)) || msg[0] == 0)
    return (EXIT_FAILURE);
  if ((lf = strchr(msg, '\n')))
    *lf = 0;
  return (EXIT_SUCCESS);
}

static void	get_srv_ret(int socketDescriptor)
{
  char		msg[MAX_MSG];
  fd_set	readSet;
  t_timeval	timeVal;
  int		msgLen;

  FD_ZERO(&readSet);
  FD_SET(socketDescriptor, &readSet);
  timeVal.tv_sec = 0;
  timeVal.tv_usec = 25000;
  bzero(msg, MAX_MSG);
  while (select(socketDescriptor + 1, &readSet, NULL, NULL, &timeVal))
    {
      if ((msgLen = read(socketDescriptor, &msg, MAX_MSG)) != -1)
	write(1, msg, msgLen);
    }
}

static int	talker(int socketDescriptor, t_entry **entry)
{
  char		msg[MAX_MSG];
  int		i;

  get_connection(socketDescriptor);
  while (strcmp(msg, "quit") != 0)
    {
      bzero(msg, sizeof(msg));
      if ((read_stdin(msg)) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      for (i = 0; entry[i]->cmd &&
	     strncmp(entry[i]->cmd, msg, strlen(entry[i]->cmd)) != 0; ++i);
      if (entry[i]->cmd != NULL)
	{
	  if ((entry[i]->fptr(msg, socketDescriptor)) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
	}
      else
	{
	  if ((dprintf(socketDescriptor, "%s", msg)) == -1)
	    return (my_perror("dprintf"));
	}
      get_srv_ret(socketDescriptor);
    }
  return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
  int		socketDescriptor;
  t_entry	**entry;

  if (ac != 3)
    {
      fprintf(stderr, "Usage: %s machine port\n", av[0]);
      return (EXIT_FAILURE);
    }
  if ((socketDescriptor = init_client(av[1], av[2])) == EXIT_FAILURE)
    return (xclose(socketDescriptor, EXIT_FAILURE));
  if (!(entry = init_fct()))
    return (xclose(socketDescriptor, EXIT_FAILURE));
  if ((talker(socketDescriptor, entry)) == EXIT_FAILURE)
    return (xclose(socketDescriptor, EXIT_FAILURE));
  return (xclose(socketDescriptor, EXIT_SUCCESS));
}
