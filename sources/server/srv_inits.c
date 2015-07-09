/*
** srv_inits.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Jul  1 11:47:46 2015 Tony Kruszkewycz
** Last update Mon Jul  6 14:28:15 2015 Tony Kruszkewycz
*/

#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netdb.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	"serveur.h"

t_entry		**init_entry(void)
{
  static char	*cmds[] =
    {"user", "ls", "cd", "get", "put", "pwd", "quit", "lls", "lpwd",
     "lcd", "help", NULL};
  static int	(*fptrtab[])(t_com, t_server *) =
    {cmd_user, cmd_ls, cmd_cd, cmd_get, cmd_put, cmd_pwd, cmd_quit,
     cmd_lls, cmd_lpwd, cmd_lcd, cmd_help, NULL};
  t_entry	**entry;
  int		i;

  if (!(entry = malloc(sizeof(t_entry *) * NB_CMD + 1)))
    return (NULL);
  for (i = 0; cmds[i]; ++i)
    {
      if (!(entry[i] = malloc(sizeof(t_entry))))
      	return (NULL);
      memset(entry[i]->cmd, 0, sizeof(entry[i]->cmd));
      strcpy(entry[i]->cmd, cmds[i]);
      entry[i]->fptr = fptrtab[i];
    }
  return (entry);
}

static void	fill_hints(struct addrinfo *hints)
{
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
}

int		init_serv(t_server *s)
{
  t_addrinfo	hints;
  t_addrinfo	*servinfo;
  int		status;

  fill_hints(&hints);
  if ((status = getaddrinfo(NULL, s->listenPort, &hints, &servinfo)) != 0)
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
      return (EXIT_FAILURE);
    }
  if ((s->listenSocket = socket(servinfo->ai_family, servinfo->ai_socktype,
				servinfo->ai_protocol)) == -1)
    return (my_perror("socket"));
  if ((bind(s->listenSocket, servinfo->ai_addr, servinfo->ai_addrlen)) == -1)
    return (my_perror("bind"));
  freeaddrinfo(servinfo);
  if (!(s->clt_info = malloc(sizeof(t_client))))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
