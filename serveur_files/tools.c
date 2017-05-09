/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:58:30 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/09 15:49:06 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	usage(char *argv, char error)
{
	if (error == 0)
		ft_printf("%s <port>\n", argv);
	else
		ft_printf("%s <port [1 - 65535]> \n", argv);
	exit(EXIT_FAILURE);
}

int		verify_path_ls(char *options, char *path)
{
	int	error;

	error = 0;
	if (ft_strstr(options, "..") != NULL)
		error++;
	if (options[0] && options[0] == '/')
		error++;
	if (path)
	{
		if (ft_strstr(path, "..") != NULL)
			error++;
		if (path[0] && path[0] == '/')
			error++;
	}
	return (error);
}

void	verify_path_cd(char *path, char *newpath)
{
	char		tmp[3000];

	if (chdir(newpath) == -1)
		exit(0);
	getcwd(tmp, 3000);
	if (!ft_strncmp(path, tmp, ft_strlen(path)))
		exit(1);
	exit(0);
}

int		verify_path_file(char *path)
{
	int	error;

	error = 0;
	if (ft_strstr(path, "..") != NULL)
		error++;
	if (path[0] && path[0] == '/')
		error++;
	return (error);
}

void	run_cd_default(struct sockaddr_in syn, int cs, char *path)
{
	char		*message;
	char		*message2;

	ft_printf("[SERVER 📶  received cd from %s %d \n",\
			inet_ntoa(syn.sin_addr));
	message = "\033[31;1;4;5;7m 🚫  cd : chdir failed \n \033[0m";
	message2 = "✅  CD SUCCESS \n";
	if (chdir(path) == -1)
		send(cs, message, ft_strlen(message), 0);
	else
		send(cs, message2, ft_strlen(message2), 0);
}
