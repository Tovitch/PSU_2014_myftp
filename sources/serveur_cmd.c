/*
** serveur_cmd.c for myftp in /home/kruszk_t/rendu/PSU_2014_myftp
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Mar 16 10:03:45 2015 kruszk_t
** Last update Sun Mar 22 23:09:11 2015 kruszk_t
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<sys/sendfile.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	"serveur.h"

int		cmd_user(t_communication c, t_server *s)
{
  (void)c;
  (void)s;
  return (EXIT_SUCCESS);
}

int		cmd_ls(t_communication c, t_server *s)
{
  if ((fork()) == 0)
    {
      dup2(s->connectSocket, 1);
      dup2(s->connectSocket, 2);
      execvp(c.cmd[0], c.cmd);
      exit(EXIT_SUCCESS);
    }
  return (EXIT_SUCCESS);
}

int		cmd_get(t_communication c, t_server *s)
{
  int		in_file;
  int		out_file;
  char		out_name[1024];
  struct stat	st;

  (void)c;
  (void)s;
  memset(out_name, 0, sizeof(out_name));
  strcat(out_name, c.cmd[2]);
  strcat(out_name, "/");
  strcat(out_name, c.cmd[1]);
  if ((in_file = open(c.cmd[1], O_RDONLY)) == -1 ||
      (out_file = open(out_name, O_CREAT | O_WRONLY, 0644)) == -1)
    {
      perror("open");
      return (EXIT_SUCCESS);
    }
  if ((stat(c.cmd[1], &st)) == -1)
    {
      perror ("stat");
      return (EXIT_FAILURE);
    }
  if ((sendfile(out_file, in_file, NULL, st.st_size)) == -1)
    {
      perror("sendfile");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int		cmd_put(t_communication c, t_server *s)
{
  (void)c;
  (void)s;
  return (EXIT_SUCCESS);
}

int		cmd_pwd(t_communication c, t_server *s)
{
  (void)c;
  if ((write(s->connectSocket, s->path, strlen(s->path))) == -1)
    {
      perror("write");
      close(s->connectSocket);
      return (EXIT_FAILURE);
    }
  if ((write(s->connectSocket, "\n", 2)) == -1)
    {
      perror("write");
      close(s->connectSocket);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int		cmd_quit(t_communication c, t_server *s)
{
  (void)c;
  (void)s;
  return (EXIT_SUCCESS);
}
