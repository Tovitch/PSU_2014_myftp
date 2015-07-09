/*
** serveur_cmd.c for myftp in /home/kruszk_t/rendu/PSU_2014_myftp
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Mar 16 10:03:45 2015 kruszk_t
** Last update Thu Jul  9 12:09:04 2015 Tony Kruszkewycz
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<sys/types.h>
#include	<sys/wait.h>
#include	"serveur.h"

int		cmd_ls(t_com c, t_server *s)
{
  int		ret;

  if ((ret = dprintf(s->connectSocket, _150)) != strlen(_150))
    {
      if ((size_t)((dprintf(s->connectSocket, _150 + ret))) !=
	  strlen(_150 + ret))
	return (my_perror("dprintf"));
    }
  if ((fork()) == 0)
    {
      dup2(s->connectSocket, 1);
      dup2(s->connectSocket, 2);
      execvp(c.cmd[0], c.cmd);
      exit(EXIT_SUCCESS);
    }
  else
    wait(NULL);
  if ((ret = dprintf(s->connectSocket, _250)) != strlen(_150))
    {
      if ((size_t)((dprintf(s->connectSocket, _250 + ret))) !=
	  strlen(_250 + ret))
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int		cmd_pwd(t_com c, t_server *s)
{
  (void)c;
  if ((dprintf(s->connectSocket, _257, s->path)) == -1)
    return (my_perror("dprintf"));
  return (EXIT_SUCCESS);
}

int		cmd_quit(t_com c, t_server *s)
{
  (void)c;
  if ((dprintf(s->connectSocket, _221)) == -1)
    return (my_perror("dprintf"));
  return (EXIT_SUCCESS);
}
