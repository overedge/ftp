/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 10:18:47 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/09 14:00:02 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int			verify_path_file(char *path)
{
	int	error;

	error = 0;
	if (ft_strstr(path, "..") != NULL)
		error++;
	if (path[0] && path[0] == '/')
		error++;
	return (error);
}

void		send_size(unsigned int size, int cs)
{
	char *str;

	str = ft_strdup("|#0000000000");
	ft_strcpy(&str[2], ft_itoa(size));
	send(cs, str, ft_strlen(str), 0);
	free(str);
}

void		send_file(int sock, int fd, struct stat buf)
{
	char		data[300000];
	int			r;

	send_size(buf.st_size, sock);
	ft_bzero(data, 300000);
	recv(sock, data, 300000, 0);
	if (ft_strcmp("OK", data))
	{
		ft_printf("%s\n", data);
		close(fd);
		return ;
	}
	else if (!ft_strcmp("OK", data))
	{
		ft_bzero(data, 300000);
		while ((r = read(fd, data, 300000)) > 0)
		{
			data[r] = '\0';
			send(sock, data, r, 0);
			ft_bzero(data, 300000);
		}
	}
	ft_printf("FILE ARE SUCCESS DOWNLOAD ✅  \n");
}

int			check(int sock, struct stat *buf, char **split)
{
	char	data[300000];
	int		fd;

	if ((fd = open(split[1], O_RDWR)) == -1)
	{
		send(sock, "KO", ft_strlen("KO"), 0);
		recv(sock, data, 300000, 0);
		ft_printf("%s\n");
		return (-1);
	}
	if (fstat(fd, buf) == -1 || (buf->st_mode & S_IFMT) != S_IFREG)
	{
		send(sock, "KO", ft_strlen("KO"), 0);
		recv(sock, data, 300000, 0);
		ft_printf("%s\n");
		close(fd);
		return (-1);
	}
	return (fd);
}

void		put_file(int sock, char *line)
{
	int			fd;
	struct stat buf;
	char		**split;

	split = ft_strsplit(line, ' ');
	if ((!split && !split[1]) || verify_path_file(split[1]) != 0)
	{
		send(sock, "KO", ft_strlen("KO"), 0);
		return ;
	}
	else
	{
		if ((fd = check(sock, &buf, split)) == -1)
			return ;
		send_file(sock, fd, buf);
	}
}
