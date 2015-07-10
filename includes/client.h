/*
** client.h for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Fri Jun 26 11:11:10 2015 Tony Kruszkewycz
** Last update Fri Jul 10 15:36:20 2015 Tony Kruszkewycz
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include		"rfc959.h"

# define		MAX_MSG 80
# define		VNO_REP -1
# define		VNO_RGHT -2
# define		MSG_RECV "Message récupéré avec succès !\n"
# define		MSG_SENT "Message envoyé avec succès !\n"

typedef struct timeval	t_timeval;

typedef struct		s_entry
{
  char			cmd[5];
  int			(*fptr)();
}			t_entry;

typedef struct		s_communication
{
  char			msg[MAX_MSG + 1];
  int			msgLength;
  char			**cmd;
}			t_com;

char			**my_str_to_wordtab(char *);

/*
** init_clt_cmd.c
*/
int			init_client_get(char *msg, int socketDescriptor);
int			init_client_put(char *msg, int socketDescriptor);

/*
** serveur.c
*/
int			read_stdin(char *msg);

/*
** init_clt.c
*/
int			init_client(char *host, char *serverPort);
t_entry			**init_fct();

/*
** clt_cmd.c
*/
int			clt_cmd_ls(char *msg, int socketDescriptor);
int			clt_cmd_pwd(char *msg, int socketDescriptor);
int			clt_cmd_cd(char *msg, int socketDescriptor);
int			clt_cmd_cd(char *msg, int socketDescriptor);
void			write_error(t_com c, int ret);
void			check_path(char *path, char *ret);
int			init_c(t_com *c, char *msg);
int			go_home();

/*
** clt_auth.c
*/
int			authentication(char *msg, int socketDescriptor);

/*
** clt_get_connection.c
*/
void			get_connection(int socketDescriptor);

/*
** xfunc.c
*/
int			xwrite(int fd, const void *buf, size_t count);
ssize_t			xread(int fd, void *buf, size_t count);
int			xclose(int fd, int ret_val);

void			my_getcwd(char *buf, char *file_name);
int			my_perror(const char *s);
int			my_send_err(const char *s, int fd, int ret);

#endif /* !CLIENT_H_ */
