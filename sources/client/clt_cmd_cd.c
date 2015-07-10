/*
** clt_cmd_cd.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Jul  3 17:11:45 2015 Tony Kruszkewycz
** Last update Fri Jul 10 15:35:05 2015 Tony Kruszkewycz
*/

#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<stdio.h>
#include	"client.h"

int		path_down(t_com c)
{
  char		*newp;

  if (!(newp = malloc(sizeof(char) * strlen(getcwd(NULL, 0)))))
    return (EXIT_FAILURE);
  newp = getcwd(NULL, 0);
  check_path(newp, c.cmd[1]);
  if ((access(newp, F_OK)) == -1)
    return (VNO_REP);
  if ((access(newp, R_OK | W_OK)) == -1)
    return (VNO_RGHT);
  chdir(newp);
  free(newp);
  return (EXIT_SUCCESS);
}

int		path_up(t_com c)
{
  char		*newp;

  if (!(newp = malloc(sizeof(char) * strlen(getcwd(NULL, 0))
		      + strlen(c.cmd[1]))))
    return (EXIT_FAILURE);
  newp = getcwd(NULL, 0);
  strcat(newp, "/");
  strcat(newp, c.cmd[1]);
  if ((access(newp, F_OK)) == -1)
    return (VNO_REP);
  if ((access(newp, R_OK | W_OK)) == -1)
    return (VNO_RGHT);
  chdir(newp);
  free(newp);
  return (EXIT_SUCCESS);
}

void		cmd_ok()
{
  printf(_250);
}

int		clt_cmd_cd(char *msg, int socketDescriptor)
{
  t_com		c;
  int		ret;

  if ((dprintf(socketDescriptor, "%s", msg)) == -1)
    return (EXIT_FAILURE);
  if ((init_c(&c, msg)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (!(c.cmd[1]))
    ret = go_home();
  else if (strncmp(c.cmd[1], "..", 2) == 0)
    ret = path_down(c);
  else
    ret = path_up(c);
  (ret == EXIT_SUCCESS) ? cmd_ok() : write_error(c, ret);
  return (EXIT_SUCCESS);
}
