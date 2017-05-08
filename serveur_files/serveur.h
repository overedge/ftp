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
#include <fcntl.h>
#include <sys/stat.h>



int			g_signal_fd;
/*
** Server instance functions 
*/
void		parse_command(char *buffer, struct sockaddr_in syn, int cs,\
			char *path);


/*
** Create Servers
*/
int			create_server(int port);
void		create_client(int cs, struct sockaddr_in syn);
void		parse_command(char *buffer, struct sockaddr_in syn, int cs,\
			char *path);

/*
** Commands
*/
void		run_ls(struct sockaddr_in syn, int cs, char *options, char *path);
void		run_simple_ls(struct sockaddr_in syn, int cs);
void		run_cd(struct sockaddr_in syn, int cs, char *path, char *new);
void		run_pwd(struct sockaddr_in syn, int cs);
void		run_quit(struct sockaddr_in syn, int cs);
void		run_get(struct sockaddr_in syn, int cs, char *path, char *file);
/*
** Tools Functions
*/
void		usage(char *argv, char error);
void		ft_exit(char *str);
void		signal_handler(void);
void		catchme(int signal);
void		send_unknow_message(int sock);
int			verify_path_ls(char *options, char *path);
void		verify_path_cd(char *path, char *newpath);
int			verify_path_file(char *path);
void		run_cd_default(struct sockaddr_in syn, int cs, char *path);
#endif
