/*
** cmd_cd.c for myftp in /home/kruszk_t/rendu/PSU_2014_myftp
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Sun Mar 22 12:44:35 2015 kruszk_t
** Last update Sun Mar 22 18:06:05 2015 kruszk_t
*/

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	"serveur.h"

int		case1(t_communication c, t_server *s, char *tmp)
{
  strcat(tmp, "/");
  strcat(tmp, c.cmd[1]);
  if (access(tmp, F_OK) == -1)
    {
      write(s->connectSocket, c.cmd[1], strlen(c.cmd[1]));
      write(s->connectSocket, ": Aucun répertoire de ce nom\n", 31);
      return (EXIT_SUCCESS);
    }
  s->path = realloc(s->path, (strlen(s->path) + strlen(c.cmd[1]) + 2));
  if (strcmp(s->path, "/") == 0)
    strcat(s->path, c.cmd[1]);
  else
    {
      strcat(s->path, "/");
      strcat(s->path, c.cmd[1]);
    }
  chdir(tmp);
  return (EXIT_SUCCESS);
}

int		case2_2(t_communication c, t_server *s, char *tmp)
{
  tmp = strndup(s->root, strlen(s->root) + strlen(c.cmd[1]));
  strcat(tmp, c.cmd[1]);
  if (access(tmp, F_OK) == -1)
    {
      if ((write(s->connectSocket, c.cmd[1], strlen(c.cmd[1]))) == -1 ||
	  (write(s->connectSocket, ": Aucun répertoire de ce nom\n", 31)) == -1)
	{
	  perror("write");
	  close(s->connectSocket);
	  return (EXIT_SUCCESS);
	}
    }
  return (EXIT_SUCCESS);
}

int		case2_3(t_communication c, t_server *s)
{
  s->path = realloc(s->path, (strlen(s->path) + strlen(c.cmd[1]) + 2));
  if (strcmp(s->path, "/") == 0)
    strcat(s->path, c.cmd[1]);
  else
    {
      strcat(s->path, "/");
      strcat(s->path, c.cmd[1]);
    }
  return (EXIT_SUCCESS);
}

int		case2(t_communication c, t_server *s, char *tmp)
{
  int		i;

  strcat(tmp, "/");
  strcat(tmp, c.cmd[1]);
  if (c.cmd[1][0] != '/' && (access(tmp, F_OK) == -1 || strncmp(c.cmd[1], "../..", 5) == 0))
    {
      write(s->connectSocket, c.cmd[1], strlen(c.cmd[1]));
      write(s->connectSocket, ": Aucun répertoire de ce nom\n", 31);
      return (EXIT_SUCCESS);
    }
  if (strcmp(c.cmd[1], "..") == 0)
    {
      for (i = strlen(s->path) - 1; s->path[i] != '/'; --i);
      s->path[i] = 0;
      if (s->path[i] == 0)
	s->path[0] = '/';
    }
  else if (c.cmd[1][0] == '/')
    case2_2(c, s, tmp);
  else
    case2_3(c, s);
  chdir(tmp);
  return (EXIT_SUCCESS);
}

int		cmd_cd(t_communication c, t_server *s)
{
  char		tmp[1024];

  memset(tmp, 0, sizeof(tmp));
  getcwd(tmp, sizeof(tmp));
  if (strcmp(s->root, tmp) == 0 && strcmp(c.cmd[1], "..") != 0)
    case1(c, s, tmp);
  else if (strcmp(s->root, tmp) != 0)
    case2(c, s, tmp);
  else
    {
      if ((write(s->connectSocket, "Accès refusé.\n", 16)) == -1)
	{
	  perror("write");
	  close(s->connectSocket);
	  return (EXIT_FAILURE);
	}
    }
  return (EXIT_SUCCESS);
}
