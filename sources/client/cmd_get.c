/*
** cmd_get.c<client> for client in /home/kruszk_t/rendu/PSU_2014_myftp
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Jul 10 14:42:09 2015 Tony Kruszkewycz
** Last update Fri Jul 10 15:23:47 2015 Tony Kruszkewycz
*/

#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<stdio.h>
#include	"client.h"

static void	strcat_cwd(t_com *c, char *str)
{
  bzero(c->msg, sizeof(c->msg));
  strcpy(c->msg, str);
  strcat(c->msg, " ");
  strcat(c->msg, getcwd(NULL, 0));
  c->msgLength = strlen(c->msg);
}

static void	confirm_recept(int socketDescriptor)
{
  char		buf[MAX_MSG + 1];

  bzero(buf, sizeof(buf));
  if ((dprintf(socketDescriptor, "recv")) == -1)
    return ;
  if ((read(socketDescriptor, buf, MAX_MSG)) != -1)
    printf("%s", buf);
}

static int	check_exist(t_com c, int socketDescriptor, int *size)
{
  bzero(c.msg, sizeof(c.msg));
  if ((read(socketDescriptor, c.msg, sizeof(c.msg))) > 0)
    {
      if (strncmp(c.msg, c.cmd[1], 4) == 0)
	{
	  printf("%s", c.msg);
	  return (EXIT_FAILURE);
	}
      *size = atoi(c.msg);
    }
  return (EXIT_SUCCESS);
}

static int	read_sock(int socketDescriptor, t_com c, int size, int fd)
{
  int		len;

  bzero(c.msg, sizeof(c.msg));
  len = 0;
  while (len < size)
    {
      bzero(c.msg, sizeof(c.msg));
      if ((c.msgLength = read(socketDescriptor, &c.msg, MAX_MSG)) > 0)
	{
	  if ((xwrite(fd, c.msg, c.msgLength)) == -1)
	    return (xclose(fd, EXIT_FAILURE));
	  len += c.msgLength;
	}
    }
  return (EXIT_SUCCESS);
}

int		init_client_get(char *msg, int socketDescriptor)
{
  t_com		c;
  int		fd;
  int		size;

  strcat_cwd(&c, msg);
  if ((xwrite(socketDescriptor, c.msg, c.msgLength)) == -1)
    return (EXIT_FAILURE);
  if (!(c.cmd = my_str_to_wordtab(msg)) && c.cmd[1] == NULL)
    return (EXIT_FAILURE);
  usleep(10000);
  if ((check_exist(c, socketDescriptor, &size)) == EXIT_FAILURE)
    return (EXIT_SUCCESS);
  bzero(c.msg, sizeof(c.msg));
  my_getcwd(c.msg, c.cmd[1]);
  if ((fd = open(c.msg, O_WRONLY | O_EXCL | O_CREAT, 0644)) == -1)
    return (EXIT_SUCCESS);
  if ((read_sock(socketDescriptor, c, size, fd)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  confirm_recept(socketDescriptor);
  return (xclose(fd, EXIT_SUCCESS));
}
