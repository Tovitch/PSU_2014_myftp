/*
** srv_put_get_cmd.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Jul  6 09:33:06 2015 Tony Kruszkewycz
** Last update Thu Jul  9 16:53:36 2015 Tony Kruszkewycz
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

static int	confirm_recept(t_server *s)
{
  if ((dprintf(s->connectSocket, _250)) == -1)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int		cmd_get(t_com c, t_server *s)
{
  int		in_file;
  ssize_t	ret;
  ssize_t	len;
  char		buf[MAX_MSG + 1];
  struct stat	st;

  bzero(buf, sizeof(buf));
  my_getcwd(buf, c.cmd[1]);
  if ((in_file = open(buf, O_RDONLY)) == -1)
    return (my_perror("open"));
  fstat(in_file, &st);
  dprintf(s->connectSocket, "%d", (int)st.st_size);
  len = 0;
  sleep(1);
  while (len < st.st_size)
    {
      bzero(buf, sizeof(buf));
      if ((ret = read(in_file, buf, MAX_MSG)) != -1)
	{
	  if ((xwrite(s->connectSocket, buf, ret)) == -1)
	    return (xclose(in_file, EXIT_FAILURE));
	  len += ret;
	}
    }
  if ((get_confim(s)) == EXIT_FAILURE)
    return (xclose(in_file, EXIT_FAILURE));
  return (xclose(in_file, EXIT_SUCCESS));
}

int		cmd_put(t_com c, t_server *s)
{
  char		buf[MAX_MSG];
  int		fd;
  ssize_t	ret;
  int		len;
  int		size;

  bzero(buf, sizeof(buf));
  my_getcwd(buf, c.cmd[1]);
  if ((fd = open(buf, O_CREAT | O_WRONLY, 0644)) == -1)
    return (my_perror("open"));
  bzero(buf, sizeof(buf));
  if ((read(s->connectSocket, buf, MAX_MSG)) > 0)
    size = atoi(buf);
  printf("%s puts %s (%do)\n", s->clt_info->nickname, c.cmd[1], size);
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
  if ((confirm_recept(s)) == EXIT_FAILURE)
    return (xclose(fd, EXIT_FAILURE));
  return (xclose(fd, EXIT_SUCCESS));
}
