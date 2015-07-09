/*
** basic.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Tue Jun 30 10:38:05 2015 Tony Kruszkewycz
** Last update Mon Jul  6 09:38:20 2015 Tony Kruszkewycz
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
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
