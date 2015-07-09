/*
** cmd_user.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Wed Jul  1 16:57:19 2015 Tony Kruszkewycz
** Last update Fri Jul  3 10:12:15 2015 Tony Kruszkewycz
*/

#include	<stdlib.h>
#include	"serveur.h"

int		cmd_user(t_com c, t_server *s)
{
  (void)c;
  if ((authentication(c, s)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
