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



typedef struct s_clients {
	char				*addr;
	struct s_clients	*next;
} t_clients;

/*
** Server instance functions 
*/


/*
** Create Servers
*/
int			create_server(int port);

/*
** Tools Functions
*/
void		usage(char *argv, char error);
void		ft_exit(char *str);
void		signal_handler(void);
void		catchme(int signal);
void		send_unknow_message(int sock);
#endif
