/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:09:44 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/09 13:54:10 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	download_file(int sock, unsigned int size, int fd)
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
	ft_printf("FILE ARE SUCCESS DOWNLOAD ✅  \n");
}

void	get_file(int sock, unsigned int size, char *line)
{
	char			**split;
	int				fd;
	char			*message;
	char			data[300000];

	message = "\033[31;1;4;5;7m This file existe in you filesystem🚫 \033[0m";
	split = ft_strsplit(line, ' ');
	ft_bzero(data, 300000);
	if (split && split[1])
	{
		fd = open(split[1], O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);
		if (fd < 0)
		{
			send(sock, "KO", ft_strlen("KO"), 0);
			ft_printf("%s\n", message);
		}
		else
			download_file(sock, size, fd);
	}
}
