/*
** cmd_cd_func.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Jul  1 10:51:54 2015 Tony Kruszkewycz
** Last update Mon Jul  6 16:35:02 2015 Tony Kruszkewycz
*/

#include	<string.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<serveur.h>

static int	count_ret(char *str)
{
  int		i;
  int		count;

  i = 0;
  count = 0;
  while (str[i])
    {
      if (str[i] && str[i + 1] && str[i] == '.' && str[i + 1] == '.')
	++count;
      ++i;
    }
  return (count);
}

void		check_path(char *path, char *ret)
{
  int		nb_ret;
  int		i;

  nb_ret = count_ret(ret);
  i = strlen(path);
  while (nb_ret != 0)
    {
      if (path[i] && path[i] == '/')
	--nb_ret;
      if (i > 0)
	--i;
    }
  if (i == 0)
    path[i] = '/';
  path[i + 1] = 0;
}

void		set_newp(t_server *s, char *newp)
{
  if (!(s->path = realloc(s->path, strlen(newp)) + 4))
    return ;
  strcat(s->path, newp);
}

void		write_err(t_com c, t_server *s, int ret)
{
  if (ret == VNO_REP || ret == EXIT_FAILURE)
    {
      if ((dprintf(s->connectSocket, _550, c.cmd[1])) == -1)
	perror("dprintf");
    }
  else if (ret == VNO_RGHT)
    {
      if ((dprintf(s->connectSocket, _550R)) == -1)
	perror("dprintf");
    }
}
