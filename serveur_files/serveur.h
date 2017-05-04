#ifndef SERVEUR_H
# define SERVEUR_H

#include "../libft_files/includes/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>




/*
** Server instance functions 
*/


/*
** Create Servers
*/
int			create_server(int port);


/*
** Commands
*/
void		run_ls(struct sockaddr_in syn, int cs);
void		run_pwd(struct sockaddr_in syn, int cs);
/*
** Tools Functions
*/
void		usage(char *argv, char error);
void		ft_exit(char *str);
void		signal_handler(void);
void		catchme(int signal);
void		send_unknow_message(int sock);
#endif
