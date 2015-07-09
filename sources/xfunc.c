/*
** xfunc.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Tue Jun 30 10:12:16 2015 Tony Kruszkewycz
** Last update Wed Jul  1 16:47:13 2015 Tony Kruszkewycz
*/

#include	<unistd.h>
#include	<stdio.h>

int		xwrite(int fd, const void *buf, size_t size)
{
  int		ret;

  if ((ret = write(fd, buf, size)) == -1)
    perror("write");
  return (ret);
}

ssize_t		xread(int fd, void *buf, size_t size)
{
  ssize_t	ret;

  if ((ret = read(fd, buf, size)) == -1)
    perror("read");
  return (ret);
}

int		xclose(int fd, int ret_val)
{
  close(fd);
  return (ret_val);
}
