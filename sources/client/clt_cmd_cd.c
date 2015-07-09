/*
** clt_cmd_cd.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Jul  3 17:11:45 2015 Tony Kruszkewycz
** Last update Mon Jul  6 12:10:44 2015 Tony Kruszkewycz
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

int		init_c(t_com *c, char *msg)
{
  strcpy(c->msg, msg);
  c->msgLength = strlen(c->msg);
  if (!(c->cmd = my_str_to_wordtab(c->msg)))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		go_home()
{
  char		buf[MAX_MSG + 1];

  bzero(buf, sizeof(buf));
  strcpy(buf, "/home/");
  strcat(buf, getlogin());
  chdir(buf);
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
