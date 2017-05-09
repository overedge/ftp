/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:27:02 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/09 13:57:39 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void		download_file(int sock, unsigned int size, int fd)
{
	unsigned int	count;
	char			data[300000];
	unsigned int	tmp;

	count = 0;
	send(sock, "OK", ft_strlen("OK"), 0);
	ft_putchar('\n');
	while (count < size)
	{
		ft_bzero(data, 300000);
		tmp = recv(sock, data, 300000, 0);
		write(fd, data, tmp);
		count += tmp;
	}
	close(fd);
}

void		get_size_file(int cs, int fd, char *path)
{
	char			data[300000];
	char			*message;

	message = "\033[31;1;4;5;7m Non exist file 🚫 \033[0m";
	send(cs, "OK", ft_strlen("OK"), 0);
	recv(cs, data, 300000, 0);
	if (data[0] && data[0] == '|' && data[1] && data[1] == '#' && data[2])
		download_file(cs, ft_atoi(&data[2]), fd);
	else
	{
		unlink(path);
		send(cs, message, ft_strlen(message), 0);
		return ;
	}
}

void		run_put(struct sockaddr_in syn, int cs, char *file)
{
	int				fd;
	char			*message;
	char			*message2;

	ft_printf("[SERVER 📶  received put from %s \n",\
			inet_ntoa(syn.sin_addr));
	message = "\033[31;1;4;5;7m This file existe in server 🚫 \033[0m";
	message2 = "\033[31;1;4;5;7m bad filename 🚫 \033[0m";
	if (file && verify_path_file(file) == 0)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);
		if (fd < 0)
			send(cs, message, ft_strlen(message), 0);
		else
			get_size_file(cs, fd, file);
	}
	else
		send(cs, message2, ft_strlen(message2), 0);
}
