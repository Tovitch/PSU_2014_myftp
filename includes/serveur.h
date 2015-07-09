/*
** serveur.h for myftp in /home/kruszk_t/Documents/PSU/MyFTP/includes
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Thu Jun 25 15:01:34 2015 Tony Kruszkewycz
** Last update Mon Jul  6 13:22:18 2015 Tony Kruszkewycz
*/

#ifndef SERVEUR_H_
# define SERVEUR_H_

# include			<sys/socket.h>
# include			<netinet/in.h>
# include			<arpa/inet.h>
# include			"rfc959.h"

# define			BACKLOG 5
# define			MAX_MSG 80
# define			LOGIN_MSG "Veuillez vous logger :\n"
# define			LOGIN_MSG_SIZE 23
# define			NB_CMD 11

# define			NO_REP "%s: Aucun répertoire de ce nom\n"
# define			VNO_REP -1
# define			NO_RGHT "Accès refusé\n"
# define			VNO_RGHT -2

# define			MSG_SENT "Message envoyé avec succès !\n"
# define			MSG_RECV "Message récupéré avec succès !\n"
# define			LOGOUT "Déconnecté ! \n"

# define			CNF "%s: commande introuvable\n"
# define			WAIT_CO "Attente de connexion TCP sur le port %s\n"

# define			PLZ_AUTH "Veuillez vous authentifier (tapez: 'user')\n"

typedef struct s_client		t_client;
typedef struct s_entry		t_entry;
typedef struct s_server		t_server;
typedef struct s_communication	t_com;

typedef struct addrinfo		t_addrinfo;

struct				s_client
{
  int				logged;
  char				*nickname;
  char				password[16];
  struct sockaddr_in		clientAddress;
};

struct				s_entry
{
  char				cmd[5];
  int				(*fptr)(t_com, t_server *);
};

struct				s_server
{
  int				listenSocket;
  int				connectSocket;
  struct s_client		*clt_info;
  struct sockaddr_in		clientAddress;
  socklen_t			clientAddressLen;
  char				*listenPort;
  char				*root;
  char				*path;
};

struct				s_communication
{
  char				msg[MAX_MSG + 1];
  int				msgLength;
  char				**cmd;
  t_entry			**entry;
};

int				cmd_user(t_com, t_server *);
int				cmd_ls(t_com, t_server *);
int				cmd_cd(t_com, t_server *);
int				cmd_get(t_com, t_server *);
int				cmd_put(t_com, t_server *);
int				cmd_pwd(t_com, t_server *);
int				cmd_quit(t_com, t_server *);
int				cmd_lls(t_com, t_server *);
int				cmd_help(t_com, t_server *);
char				**my_str_to_wordtab(char *);

/*
** serveur.c
*/
void				print_client_entry(t_com *c, t_client *info);

/*
** run_serv.c
*/
int				run_serv(t_server *s, t_com c);

/*
** srv_inits.c
*/
t_entry				**init_entry(void);
int				init_serv(t_server *s);

/*
** srv_auth.c
*/
int				authentication(t_com c, t_server *s);
void				fill_client(t_client *client, struct sockaddr_in clientAddress);

/*
** cmd_cd_func.c
*/
void				write_err(t_com c, t_server *s,
					  int ret);
void				set_newp(t_server *s, char *newp);
void				check_path(char *path, char *ret);

/*
** cmd_empty.c
*/
int				cmd_lls(t_com c, t_server *s);
int				cmd_lpwd(t_com c, t_server *s);
int				cmd_lcd(t_com c, t_server *s);

/*
** xfunc.c
*/
int				xwrite(int fd, const void *buf, size_t count);
ssize_t				xread(int fd, void *buf, size_t count);
int				xclose(int fd, int ret_val);

/*
** basic.c
*/
int				my_perror(const char *s);
void				my_getcwd(char *buf, char *file_name);
char				*my_strdup(char *str);

#endif /* !SERVEUR_H_ */
