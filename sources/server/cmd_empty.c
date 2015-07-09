/*
** cmd_empty.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Jul  3 16:39:48 2015 Tony Kruszkewycz
** Last update Fri Jul  3 17:10:02 2015 Tony Kruszkewycz
*/

#include	<stdlib.h>
#include	"serveur.h"

int		cmd_lls(t_com c, t_server *s)
{
  (void)c;
  (void)s;
  return (EXIT_SUCCESS);
}

int		cmd_lpwd(t_com c, t_server *s)
{
  (void)c;
  (void)s;
  return (EXIT_SUCCESS);
}

int		cmd_lcd(t_com c, t_server *s)
{
  (void)c;
  (void)s;
  return (EXIT_SUCCESS);
}
