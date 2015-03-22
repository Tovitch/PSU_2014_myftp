##
## Makefile for myftp in /home/kruszk_t/rendu/TPs/tp_myftp/tests
## 
## Made by kruszk_t
## Login   <kruszk_t@epitech.net>
## 
## Started on  Sat Mar 14 10:47:36 2015 kruszk_t
## Last update Sun Mar 22 12:44:56 2015 kruszk_t
##

SRC_SRV		= sources/serveur.c		\
		  sources/serveur_cmd.c		\
		  sources/cmd_cd.c		\
		  sources/my_str_to_wordtab.c

SRC_CLT		= sources/client.c

NAME_SRV	= serveur

NAME_CLT	= client

OBJ_SRV		= $(SRC_SRV:.c=.o)

OBJ_CLT		= $(SRC_CLT:.c=.o)

CC		= gcc

RM		= rm -f

CFLAGS		+= -Wall -Wextra -W -I./includes

all:		$(NAME_SRV) $(NAME_CLT)

$(NAME_SRV):	$(OBJ_SRV)
		$(CC) -o $(NAME_SRV) $(OBJ_SRV)

$(NAME_CLT):	$(OBJ_CLT)
		$(CC) -o $(NAME_CLT) $(OBJ_CLT)

clean:
		$(RM) $(OBJ_SRV) $(OBJ_CLT)

fclean:		clean
		rm -f $(NAME_SRV) $(NAME_CLT)

re:		fclean all

.PHONY:		all clean fclean re
