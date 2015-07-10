/*
** basic.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Tue Jun 30 10:38:05 2015 Tony Kruszkewycz
** Last update Fri Jul 10 12:06:42 2015 Tony Kruszkewycz
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<errno.h>
#include	"serveur.h"

void		my_getcwd(char *buf, char *file_name)
{
  bzero(buf, MAX_MSG);
  strcat(buf, getcwd(NULL, 0));
  strcat(buf, "/");
  if (file_name)
    strcat(buf, file_name);
}

int		my_perror(const char *s)
{
  perror(s);
  return (EXIT_FAILURE);
}

int		my_send_err(const char *s, int fd, int ret)
{
  if (fd != -1)
    {
      if ((fork()) == 0)
	{
	  dup2(fd, STDERR_FILENO);
	  perror(s);
	  exit(0);
	}
    }
  else
    perror(s);
  return (ret);
}

char			*my_strdup(char *str)
{
  char			*ret;
  int			i;

  if (!(ret = malloc(sizeof(char) * strlen(str) + 1)))
    return (NULL);
  for (i = 0; str[i]; ++i)
    ret[i] = str[i];
  return (ret);
}
