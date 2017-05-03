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
#include <sys/types.h>
/*
** Client instance functions 
*/
int			create_client(char *addr, int port);
void		parse_inputs(int sock);

/*
** Tools Functions
*/
void		usage(char *argv, char error);
void		ft_exit(char *str);

#endif
