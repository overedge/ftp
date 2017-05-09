/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 09:17:32 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/09 14:01:32 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	run_ls(struct sockaddr_in syn, int cs, char *options, char *path)
{
	pid_t		father;
	char *const	parmlist[] = {"/bin/ls", options, path, NULL};
	char		*message;

	message = "\033[31;1;4;5;7m 🚫  ls : only in directory \n \
	(no subdirectory) usage of ls [options] [dir] \033[0m";
	ft_printf("[SERVER 📶  received ls from %s \n",\
			inet_ntoa(syn.sin_addr));
	if (verify_path_ls(options, path) != 0)
	{
		send(cs, message, ft_strlen(message), 0);
		return ;
	}
	father = fork();
	if (father == -1)
		ft_exit("FORk ERROR\n");
	else if (father == 0)
	{
		dup2(cs, 1);
		dup2(cs, 2);
		execv("/bin/ls", parmlist);
	}
	else
		wait4(father, NULL, 0, NULL);
}

void	run_cd(struct sockaddr_in syn, int cs, char *path, char *new)
{
	pid_t		father;
	char		*message;
	char		*message2;
	int			status;

	ft_printf("[SERVER 📶  received cd from %s \n",\
			inet_ntoa(syn.sin_addr));
	message = "\033[31;1;4;5;7m 🚫  cd : Bad path \n\033[0m";
	message2 = "✅  CD SUCCESS \n";
	father = fork();
	if (father == -1)
		ft_exit("FORk ERROR\n");
	else if (father == 0)
		verify_path_cd(path, new);
	else
		wait4(father, &status, 0, NULL);
	if (WEXITSTATUS(status) == 0)
		send(cs, message, ft_strlen(message), 0);
	else
	{
		if (chdir(new) == -1)
			send(cs, message, ft_strlen(message), 0);
		else
			send(cs, message2, ft_strlen(message2), 0);
	}
}

void	run_simple_ls(struct sockaddr_in syn, int cs)
{
	pid_t		father;
	char *const	parmlist[] = {"/bin/ls", NULL};

	ft_printf("[SERVER 📶  received ls from %s \n",\
			inet_ntoa(syn.sin_addr));
	father = fork();
	if (father == -1)
		ft_exit("FORk ERROR\n");
	else if (father == 0)
	{
		dup2(cs, 1);
		dup2(cs, 2);
		execv("/bin/ls", parmlist);
	}
	else
		wait4(father, NULL, 0, NULL);
}

void	run_pwd(struct sockaddr_in syn, int cs)
{
	pid_t		father;
	char *const	parmlist[] = {"/bin/pwd", NULL};

	ft_printf("[SERVER 📶  received pwd from %s \n",\
			inet_ntoa(syn.sin_addr));
	father = fork();
	if (father == -1)
		ft_exit("FORk ERROR\n");
	else if (father == 0)
	{
		dup2(cs, 1);
		dup2(cs, 2);
		execv("/bin/pwd", parmlist);
	}
	else
		wait4(father, NULL, 0, NULL);
}

void	run_quit(struct sockaddr_in syn, int cs)
{
	ft_printf("[SERVER 🚫  ] user disconnected %s \n",
			inet_ntoa(syn.sin_addr));
	close(cs);
	exit(EXIT_SUCCESS);
}
