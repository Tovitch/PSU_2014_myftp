/*
** cmd_put.c for myftp in /home/kruszk_t/rendu/PSU_2014_myftp
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Jul 10 09:42:50 2015 Tony Kruszkewycz
** Last update Fri Jul 10 15:44:28 2015 Tony Kruszkewycz
*/

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<string.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"serveur.h"

static int	confirm_recept(t_server *s)
{
  if ((dprintf(s->connectSocket, _250)) == -1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

static int	read_sock(t_server *s, int fd, int size)
{
  char		buf[MAX_MSG];
  ssize_t	ret;
  ssize_t	len;

  len = 0;
  while (len < size)
    {
      bzero(buf, sizeof(buf));
      if ((ret = read(s->connectSocket, buf, MAX_MSG)) > 0)
	{
	  if ((xwrite(fd, buf, ret)) == -1)
	    return (xclose(fd, EXIT_FAILURE));
	  len += ret;
	}
    }
  return (EXIT_SUCCESS);
}

int		get_size(t_com c, t_server *s, int *size)
{
  char		buf[MAX_MSG];

  bzero(buf, sizeof(buf));
  if ((read(s->connectSocket, buf, MAX_MSG)) > 0)
    {
      if (strncmp(buf, c.cmd[1], strlen(c.cmd[1])) == 0)
	return (EXIT_FAILURE);
      *size = atoi(buf);
    }
  return (EXIT_SUCCESS);
}

int		cmd_put(t_com c, t_server *s)
{
  char		buf[MAX_MSG];
  int		fd;
  int		size;

  if (!c.cmd[1])
    {
      dprintf(s->connectSocket, "Usage: put _FILE_\n");
      return (EXIT_SUCCESS);
    }
  if ((get_size(c, s, &size)) == EXIT_FAILURE)
    return (EXIT_SUCCESS);
  my_getcwd(buf, c.cmd[1]);
  if ((fd = open(buf, O_CREAT | O_EXCL| O_WRONLY, 0644)) == -1)
    return (my_send_err(c.cmd[1], -1, EXIT_SUCCESS));
  printf("\t--> %s puts %s (%d o)\n", s->clt_info->nickname, c.cmd[1], size);
  if ((read_sock(s, fd, size)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if ((confirm_recept(s)) == EXIT_FAILURE)
    return (xclose(fd, EXIT_FAILURE));
  return (xclose(fd, EXIT_SUCCESS));
}
