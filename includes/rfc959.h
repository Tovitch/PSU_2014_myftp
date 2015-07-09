/*
** rfc959.h for myftp in /home/kruszk_t/Documents/PSU/MyFTP
**
** Made by Tony Kruszkewycz
** Login   <kruszk_t@epitech.net>
**
** Started on  Mon Jul  6 10:50:52 2015 Tony Kruszkewycz
** Last update Mon Jul  6 12:06:02 2015 Tony Kruszkewycz
*/

#ifndef RFC959_H_
# define RFC959_H_

/*
** RFC959 codes & messages
*/

# define			_214 "214: Help message.\n\
On how to use the server or the meaning of a particular\n\
non-standard command.  This reply is useful only to the\n\
human user.\r\n"
# define			HELP_MSG "\nuser: spécifie l’utilisateur au serveur et demande un mot de passe.\n\
ls: liste le répertoire courant du serveur.\n\
cd: change le répertoire courant du serveur.\n\
get _FILE_: transfère le fichier _FILE_ du serveur vers le client.\n\
put _FILE_: transfère le fichier _FILE_ du client vers le serveur.\n\
pwd: affiche le répertoire courant du serveur.\n\
quit: coupe la connexion et sort du programme.\n\
lls: liste le répertoire courant du client.\n\
lcd: change le répertoire courant du client.\n\
lpwd: affiche le répertoire courant du client.\r\n"
# define			_220 "220: Service ready for new user.\r\n"
# define			_221 "221: Service closing control connection.\r\n"
# define			_226 "226: The entire file was successfully received and stored.\r\n"
# define			_230 "230: User logged in, proceed.\r\n"
# define			_250 "250: Requested file action okay, completed.\r\n"
# define			_257 "257: \"%s\"\r\n"
# define			_331 "331: User name okay, need password.\r\n"
# define			_550 "550: %s: No such file or directory.\r\n"
# define			_550R "550: Access denied.\r\n"

#endif /* !RFC959_H_ */
