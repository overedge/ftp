/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 13:23:00 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/08 16:25:28 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void		send_size(unsigned int size, int cs)
{
	char *str;

	str = ft_strdup("|#0000000000");
	ft_strcpy(&str[2], ft_itoa(size));
	send(cs, str, ft_strlen(str), 0);
	free(str);
}

void		send_file(struct sockaddr_in syn, int cs, int fd, struct stat buf)
{
	char		data[300000];
	int			r;

	send_size(buf.st_size, cs);
	ft_printf("[SERVER 📶  received get from %s - 🌐  USER_ID = %d \n",\
			inet_ntoa(syn.sin_addr), cs);
	ft_bzero(data, 300000);
	recv(cs, data, 300000, 0);
	if (!ft_strcmp("KO", data))
	{
		close(fd);
		return ;
	}
	else if (!ft_strcmp("OK", data))
	{
		ft_bzero(data, 300000);
		while ((r = read(fd, data, 300000)) > 0)
		{
			data[r] = '\0';
			send(cs, data, r, 0);
			ft_bzero(data, 300000);
		}
	}
}

void		run_get(struct sockaddr_in syn, int cs, char *path, char *file)
{
	char		*message;
	int			fd;
	struct stat buf;

	message = "\033[31;1;4;5;7m 🚫  get Bad path or bad file \n\033[0m";
	if (!file || verify_path_file(file) != 0)
	{
		send(cs, message, ft_strlen(message), 0);
		return ;
	}
	else
	{
		if ((fd = open(file, O_RDWR)) == -1)
		{
			send(cs, message, ft_strlen(message), 0);
			return ;
		}
		if (fstat(fd, &buf) == -1 || (buf.st_mode & S_IFMT) != S_IFREG)
		{
			send(cs, message, ft_strlen(message), 0);
			close(fd);
			return ;
		}
		send_file(syn, cs, fd, buf);
	}
}
