/*
** init_clt_cmd.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Jul  1 17:37:38 2015 Tony Kruszkewycz
** Last update Fri Jul 10 15:28:17 2015 Tony Kruszkewycz
*/

#include	<string.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<stdio.h>
#include	"client.h"

int		get_confirm(int socketDescriptor)
{
  char		buf[MAX_MSG + 1];
  int		ret;

  bzero(buf, sizeof(buf));
  if ((ret = read(socketDescriptor, buf, MAX_MSG)) != -1)
    printf("%s", buf);
  return (EXIT_SUCCESS);
}

static int	read_file(int fd, int socketDescriptor)
{
  char		buf[MAX_MSG + 1];
  ssize_t	ret;

  ret = MAX_MSG;
  while (ret == MAX_MSG)
    {
      bzero(buf, sizeof(buf));
      if ((ret = read(fd, buf, MAX_MSG)) != -1)
	{
	  if ((xwrite(socketDescriptor, buf, ret)) == -1)
	    return (xclose(fd, EXIT_FAILURE));
	}
    }
  return (EXIT_SUCCESS);
}

int		init_client_put(char *msg, int socketDescriptor)
{
  char		**tab;
  char		buf[MAX_MSG + 1];
  int		fd;
  struct stat	st;

  if ((xwrite(socketDescriptor, msg, strlen(msg))) == -1)
    return (EXIT_FAILURE);
  if (!(tab = my_str_to_wordtab(msg)))
    return (EXIT_FAILURE);
  my_getcwd(buf, tab[1]);
  if ((fd = open(buf, O_RDONLY)) == -1)
    return (my_send_err(tab[1], -1, EXIT_SUCCESS));
  lstat(buf, &st);
  dprintf(socketDescriptor, "%d", (int)st.st_size);
  usleep(10000);
  if ((read_file(fd, socketDescriptor)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if ((get_confirm(socketDescriptor)) == EXIT_FAILURE)
    return (xclose(fd, EXIT_FAILURE));
  return (xclose(fd, EXIT_SUCCESS));
}
