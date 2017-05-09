/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:50:12 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/09 13:52:43 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "../libft_files/includes/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/socket.h>
# include <netdb.h>
# include <stdio.h>
# include <stdio.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

int			g_actual_socket;
/*
** Client instance functions
*/
int			create_client(char *addr, int port);
void		parse_inputs(int sock);
void		get_file(int sock, unsigned int size, char *line);
void		put_file(int sock, char *line);
/*
** Tools Functions
*/
void		usage(char *argv, char error);
void		ft_exit(char *str);
#endif
