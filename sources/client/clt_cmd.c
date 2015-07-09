/*
** clt_cmd.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Jul  3 16:12:46 2015 Tony Kruszkewycz
** Last update Mon Jul  6 10:50:18 2015 Tony Kruszkewycz
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	"client.h"

int		clt_cmd_ls(char *msg, int socketDescriptor)
{
  char		**tab;
  char		buf[MAX_MSG + 1];

  bzero(buf, sizeof(buf));
  if ((dprintf(socketDescriptor, "%s", msg)) == -1)
    return (EXIT_FAILURE);
  if ((fork()) == 0)
    {
      msg += 1;
      if (!(tab = my_str_to_wordtab(msg)))
	return (EXIT_FAILURE);
      execvp(tab[0], tab);
      exit(EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int		clt_cmd_pwd(char *msg, int socketDescriptor)
{
  char		buf[MAX_MSG + 1];

  if ((dprintf(socketDescriptor, "%s", msg)) == -1)
    return (EXIT_FAILURE);
  bzero(buf, sizeof(buf));
  getcwd(buf, sizeof(buf));
  printf(_257, buf);
  return (EXIT_SUCCESS);
}
