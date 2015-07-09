/*
** init_clt_cmd.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Jul  1 17:37:38 2015 Tony Kruszkewycz
** Last update Thu Jul  9 16:53:29 2015 Tony Kruszkewycz
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

void		confirm_recept(int socketDescriptor)
{
  char		buf[MAX_MSG + 1];

  bzero(buf, sizeof(buf));
  if ((dprintf(socketDescriptor, "recv")) == -1)
    return ;
  if ((read(socketDescriptor, buf, MAX_MSG)) != -1)
    printf("%s", buf);
}

int		init_client_get(char *msg, int socketDescriptor)
{
  t_com		c;
  int		fd;
  int		size;
  int		len;

  strcat_cwd(&c, msg);
  if ((xwrite(socketDescriptor, c.msg, c.msgLength)) == -1)
    return (EXIT_FAILURE);
  if (!(c.cmd = my_str_to_wordtab(msg)) && c.cmd[1] == NULL)
    return (EXIT_FAILURE);
  bzero(c.msg, sizeof(c.msg));
  my_getcwd(c.msg, c.cmd[1]);
  if ((fd = open(c.msg, O_WRONLY | O_CREAT, 0644)) == -1)
    return (my_perror("open"));
  bzero(c.msg, sizeof(c.msg));
  if ((read(socketDescriptor, c.msg, sizeof(c.msg))) > 0)
    size = atoi(c.msg);
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
  confirm_recept(socketDescriptor);
  return (xclose(fd, EXIT_SUCCESS));
}

int		get_confirm(int socketDescriptor)
{
  char		buf[MAX_MSG + 1];
  int		ret;

  bzero(buf, sizeof(buf));
  if ((ret = read(socketDescriptor, buf, MAX_MSG)) != -1)
    printf("%s", buf);
  return (EXIT_SUCCESS);
}

int		init_client_put(char *msg, int socketDescriptor)
{
  char		**tab;
  char		buf[MAX_MSG + 1];
  int		fd;
  ssize_t	ret;
  ssize_t	len;
  struct stat	st;

  if ((xwrite(socketDescriptor, msg, strlen(msg))) == -1)
    return (EXIT_FAILURE);
  if (!(tab = my_str_to_wordtab(msg)))
    return (EXIT_FAILURE);
  my_getcwd(buf, tab[1]);
  if ((fd = open(buf, O_RDONLY)) == -1)
    return (my_perror("open"));
  fstat(fd, &st);
  dprintf(socketDescriptor, "%d", (int)st.st_size);
  len = 0;
  ret = MAX_MSG;
  sleep(1);
  while (ret == MAX_MSG)
    {
      bzero(buf, sizeof(buf));
      if ((ret = read(fd, buf, MAX_MSG)) != -1)
	{
	  if ((xwrite(socketDescriptor, buf, ret)) == -1)
	    return (xclose(fd, EXIT_FAILURE));
	  len += ret;
	}
    }
  if ((get_confirm(socketDescriptor)) == EXIT_FAILURE)
    return (xclose(fd, EXIT_FAILURE));
  return (xclose(fd, EXIT_SUCCESS));
}
