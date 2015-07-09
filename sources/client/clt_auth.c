/*
** clt_auth.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Jul  1 18:06:36 2015 Tony Kruszkewycz
** Last update Mon Jul  6 10:49:02 2015 Tony Kruszkewycz
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	"client.h"

int		authentication(char *msg, int socketDescriptor)
{
  t_com		c;

  if ((dprintf(socketDescriptor, "%s", msg)) == -1)
    return (my_perror("dprintf"));
  bzero(c.msg, sizeof(c.msg));
  if ((xread(socketDescriptor, c.msg, MAX_MSG)) == -1)
    return (EXIT_FAILURE);
  printf("%s", c.msg);
  return (EXIT_SUCCESS);
}
