/*
** cmd_cd.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Thu Jun 25 15:56:46 2015 Tony Kruszkewycz
** Last update Thu Jul  9 11:45:25 2015 Tony Kruszkewycz
*/

#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"serveur.h"

int		path_down(t_com c, t_server *s)
{
  char		*newp;

  if (!(newp = malloc(sizeof(char) * strlen(getcwd(NULL, 0)))))
    return (EXIT_FAILURE);
  newp = getcwd(NULL, 0);
  check_path(newp, c.cmd[1]);
  if (strlen(newp) < strlen(s->root))
    return (VNO_RGHT);
  if ((access(newp, F_OK)) == -1)
    return (VNO_REP);
  if ((access(newp, R_OK | W_OK)) == -1)
    return (VNO_RGHT);
  chdir(newp);
  check_path(s->path, c.cmd[1]);
  free(newp);
  return (EXIT_SUCCESS);
}

int		path_up(t_com c, t_server *s)
{
  char		*newp;
  size_t	size;

  newp = NULL;
  size = strlen(getcwd(NULL, 0)) + strlen(c.cmd[1]) + 1;
  newp = getcwd(newp, size);
  strcat(newp, "/");
  strcat(newp, c.cmd[1]);
  if ((access(newp, F_OK)) == -1)
    return (VNO_REP);
  if ((access(newp, R_OK | W_OK)) == -1)
    return (VNO_RGHT);
  chdir(newp);
  set_newp(s, c.cmd[1]);
  free(newp);
  return (EXIT_SUCCESS);
}

void		cmd_ok(t_server *s)
{
  if ((dprintf(s->connectSocket, _250)) == -1)
    return ;
}

int		cmd_cd(t_com c, t_server *s)
{
  int		ret;

  if (!c.cmd[1] || strncmp(c.cmd[1], "/", 1) == 0)
    chdir(s->root);
  else if (strncmp(c.cmd[1], "..", 2) == 0)
    ret = path_down(c, s);
  else
    ret = path_up(c, s);
  (ret == EXIT_SUCCESS) ? cmd_ok(s) : write_err(c, s, ret);
  return (EXIT_SUCCESS);
}
