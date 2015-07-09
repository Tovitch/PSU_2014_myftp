/*
** clt_cmd_cd_func.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Jul  3 17:15:43 2015 Tony Kruszkewycz
** Last update Fri Jul  3 17:24:06 2015 Tony Kruszkewycz
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

void		write_error(t_com c, int ret)
{
  if (ret == VNO_REP || ret == EXIT_FAILURE)
    printf(NO_REP, c.cmd[1]);
  else if (ret == VNO_RGHT)
    printf(NO_RGHT);
}
