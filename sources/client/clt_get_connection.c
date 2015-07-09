/*
** clt_get_connection.c for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Jul  3 12:06:51 2015 Tony Kruszkewycz
** Last update Fri Jul  3 12:07:18 2015 Tony Kruszkewycz
*/

#include	<unistd.h>
#include	<string.h>
#include	"client.h"

void		get_connection(int socketDescriptor)
{
  char		msg[MAX_MSG + 1];
  int		ret;

  ret = MAX_MSG;
  bzero(msg, sizeof(msg));
  while (ret == MAX_MSG)
    {
      if ((ret = read(socketDescriptor, msg, MAX_MSG)) != -1)
	write(1, msg, ret);
      bzero(msg, sizeof(msg));
    }
}
