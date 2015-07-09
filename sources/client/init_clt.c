/*
** init_clt.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Jul  1 18:08:47 2015 Tony Kruszkewycz
** Last update Mon Jul  6 09:38:41 2015 Tony Kruszkewycz
*/

#include		<stdlib.h>
#include		<stdio.h>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netdb.h>
#include		<string.h>
#include		"client.h"

t_entry		**init_fct()
{
  static char	*cmds[] =
    {"user", "get ", "put ", "lls", "lpwd", "lcd", NULL};
  static int	(*fptrtab[])() =
    {authentication, init_client_get, init_client_put, clt_cmd_ls,
     clt_cmd_pwd, clt_cmd_cd, NULL};
  t_entry	**entry;
  int		i;

  if (!(entry = malloc(sizeof(t_entry) * 5)))
    return (NULL);
  for (i = 0; cmds[i]; ++i)
    {
      if (!(entry[i] = malloc(sizeof(t_entry))))
	return (NULL);
      bzero(entry[i]->cmd, sizeof(entry[i]->cmd));
      strcpy(entry[i]->cmd, cmds[i]);
      entry[i]->fptr = fptrtab[i];
    }
  return (entry);
}

int			init_client(char *host, char *serverPort)
{
  struct addrinfo	hints;
  struct addrinfo	*servinfo;
  int			status;
  int			socketDescriptor;

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;
  if ((status = getaddrinfo(host, serverPort, &hints, &servinfo)) != 0)
    {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
      return (EXIT_FAILURE);
    }
  if ((socketDescriptor = socket(servinfo->ai_family,
				 servinfo->ai_socktype,
				 servinfo->ai_protocol)) == -1)
    return (my_perror("socket"));
  if ((connect(socketDescriptor, servinfo->ai_addr,
	       servinfo->ai_addrlen)) == -1)
    return (my_perror("connect"));
  freeaddrinfo(servinfo);
  return (socketDescriptor);
}
