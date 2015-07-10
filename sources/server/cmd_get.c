/*
** srv_put_get_cmd.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Jul  6 09:33:06 2015 Tony Kruszkewycz
** Last update Fri Jul 10 14:37:24 2015 Tony Kruszkewycz
*/

#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	"serveur.h"

static int	get_confim(t_server *s)
{
  char		buf[MAX_MSG + 1];
  int		ret;

  bzero(buf, sizeof(buf));
  if ((ret = read(s->connectSocket, buf, MAX_MSG)) != -1)
    {
      if ((strcmp(buf, "recv")) == 0)
	{
	  if ((dprintf(s->connectSocket, _226)) == -1)
	    return (EXIT_FAILURE);
	}
    }
  return (EXIT_SUCCESS);
}

static int	read_file(t_server *s, int fd, ssize_t size)
{
  char		buf[MAX_MSG + 1];
  ssize_t	len;
  ssize_t	ret;

  len = 0;
  while (len < size)
    {
      bzero(buf, sizeof(buf));
      if ((ret = read(fd, buf, MAX_MSG)) != -1)
	{
	  if ((xwrite(s->connectSocket, buf, ret)) == -1)
	    return (xclose(fd, EXIT_FAILURE));
	  len += ret;
	}
    }
  return (EXIT_SUCCESS);
}

int		cmd_get(t_com c, t_server *s)
{
  int		in_file;
  char		buf[MAX_MSG + 1];
  struct stat	st;

  if (!(c.cmd[1]))
    {
      dprintf(s->connectSocket, "Usage: put _FILE_\n");
      return (EXIT_SUCCESS);
    }
  bzero(buf, sizeof(buf));
  my_getcwd(buf, c.cmd[1]);
  if ((in_file = open(buf, O_RDONLY)) == -1)
    return (my_send_err(c.cmd[1], s->connectSocket, EXIT_SUCCESS));
  fstat(in_file, &st);
  dprintf(s->connectSocket, "%d", (int)st.st_size);
  printf("\t--> %s gets %s (%d o)\n", s->clt_info->nickname, c.cmd[1],
	 (int)st.st_size);
  sleep(1);
  if ((read_file(s, in_file, st.st_size)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if ((get_confim(s)) == EXIT_FAILURE)
    return (xclose(in_file, EXIT_FAILURE));
  return (xclose(in_file, EXIT_SUCCESS));
}
