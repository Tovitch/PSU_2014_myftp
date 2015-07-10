##
## Makefile for myftp in /home/kruszk_t/rendu/TPs/tp_myftp/tests
## 
## Made by kruszk_t
## Login   <kruszk_t@epitech.net>
## 
## Started on  Sat Mar 14 10:47:36 2015 kruszk_t
## Last update Fri Jul 10 09:44:35 2015 Tony Kruszkewycz
##

PORT		= 4242

SRC_SRV		= sources/server/serveur.c		\
		  sources/server/srv_inits.c		\
		  sources/server/srv_auth.c		\
		  sources/server/run_serv.c		\
		  sources/server/serveur_cmd.c		\
		  sources/server/cmd_user.c		\
		  sources/server/cmd_cd.c		\
		  sources/server/cmd_cd_func.c		\
		  sources/server/cmd_help.c		\
		  sources/server/cmd_get.c		\
		  sources/server/cmd_put.c		\
		  sources/server/cmd_empty.c		\
		  sources/basic.c			\
		  sources/my_str_to_wordtab.c		\
		  sources/xfunc.c

SRC_CLT		= sources/client/client.c		\
		  sources/client/init_clt.c		\
		  sources/client/init_clt_cmd.c		\
		  sources/client/clt_auth.c		\
		  sources/client/clt_cmd.c		\
		  sources/client/clt_cmd_cd.c		\
		  sources/client/clt_cmd_cd_func.c	\
		  sources/client/clt_get_connection.c	\
		  sources/xfunc.c			\
		  sources/basic.c			\
		  sources/my_str_to_wordtab.c

NAME_SRV	= serveur

NAME_CLT	= client

OBJ_SRV		= $(SRC_SRV:.c=.o)

OBJ_CLT		= $(SRC_CLT:.c=.o)

CC		= gcc

RM		= rm -f

CFLAGS		+= -Wall -Wextra -W -I./includes -g3

all:		$(NAME_SRV) $(NAME_CLT)

$(NAME_SRV):	$(OBJ_SRV)
		$(CC) -o $(NAME_SRV) $(OBJ_SRV)

$(NAME_CLT):	$(OBJ_CLT)
		$(CC) -o $(NAME_CLT) $(OBJ_CLT)

clt:
		./$(NAME_CLT) localhost $(PORT)

srv:
		./$(NAME_SRV) $(PORT)

clean:
		$(RM) $(OBJ_SRV) $(OBJ_CLT)

fclean:		clean
		rm -f $(NAME_SRV) $(NAME_CLT)

re:		fclean all

.PHONY:		all clean fclean re
