/*
** my_str_to_wordtab.c for myftp in /home/kruszk_t/rendu/PSU_2014_myftp
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Mar 16 09:14:05 2015 kruszk_t
** Last update Mon Mar 16 10:14:17 2015 kruszk_t
*/

#include	<stdlib.h>
#include	<string.h>

static int	count_word(char *str)
{
  int		i;
  int		count;

  i = 0;
  count = 1;
  while (str[i])
    {
      if (str[i] == ' ')
	++count;
      ++i;
    }
  return (count);
}

static int	word_len(char *str, int i)
{
  int		count;

  for (count = 0; str[i] && str[i] != ' '; ++i, ++count);
  return (count);
}

char		**my_str_to_wordtab(char *str)
{
  char		**tab;
  int		i;
  int		y, x;
  int		stop;

  if (!(tab = malloc(sizeof(char *) * count_word(str) + 1)))
    return (NULL);
  stop = strlen(str);
  for (i = 0, y = 0; i < stop; ++i, ++y)
    {
      for (; str[i] == ' ' || str[i] == '\t'; ++i);
      if (i != stop)
	{
	  if (!(tab[y] = malloc(sizeof(char) * word_len(str, i) + 1)))
	    return (NULL);
	  for (x = 0; str[i] && str[i] != ' '; ++x, ++i)
	    tab[y][x] = str[i];
	  tab[y][x] = 0;
	}
    }
  tab[y] = NULL;
  return (tab);
}
