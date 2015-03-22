/*
** serveur.h for myftp in /home/kruszk_t/rendu/TPs/tp_myftp/tests
**
** Made by kruszk_t
** Login   <kruszk_t@epitech.net>
**
** Started on  Sun Mar 15 14:22:57 2015 kruszk_t
** Last update Sun Mar 22 13:06:01 2015 kruszk_t
*/

#ifndef SERVEUR_H_
# define SERVEUR_H_

# include		<sys/socket.h>
# include		<netinet/in.h>
# include		<arpa/inet.h>

# define		BACKLOG 5
# define		MAX_MSG 80
# define		LOGIN_MSG "Veuillez vous logger :\n"
# define		LOGIN_MSG_SIZE 23
# define		NB_CMD 7

typedef struct s_client t_client;
typedef struct s_entry	t_entry;
typedef struct s_server	t_server;
typedef struct s_communication t_communication;

struct			s_client
{
  int			logged;
  char			*nickname;
  char			password[16];
  struct sockaddr_in	clientAddress;
};

struct			s_entry
{
  char			cmd[5];
  int			(*fptr)(t_communication, t_server *);
};

struct			s_server
{
  int			listenSocket;
  int			connectSocket;
  struct sockaddr_in	clientAddress;
  socklen_t		clientAddressLen;
  char			*listenPort;
  char			*root;
  char			*path;
};

struct			s_communication
{
  char			msg[MAX_MSG + 1];
  int			msgLength;
  char			**cmd;
  t_entry		**entry;
};

int			cmd_user(t_communication, t_server *);
int			cmd_ls(t_communication, t_server *);
int			cmd_cd(t_communication, t_server *);
int			cmd_get(t_communication, t_server *);
int			cmd_put(t_communication, t_server *);
int			cmd_pwd(t_communication, t_server *);
int			cmd_quit(t_communication, t_server *);
char			**my_str_to_wordtab(char *);

#endif /* !SERVEUR_H_ */
