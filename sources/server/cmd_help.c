/*
** cmd_help.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Jul  6 11:46:44 2015 Tony Kruszkewycz
** Last update Mon Jul  6 11:54:22 2015 Tony Kruszkewycz
*/

#include	<stdlib.h>
#include	<stdio.h>
#include	"serveur.h"

int		cmd_help(t_com c, t_server *s)
{
  (void)c;
  if ((dprintf(s->connectSocket, _214)) == -1)
    return (EXIT_FAILURE);
  if ((dprintf(s->connectSocket, HELP_MSG)) == -1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
