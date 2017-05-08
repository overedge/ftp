/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 13:22:52 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/08 13:22:54 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*protocole;
	struct sockaddr_in	syn;

	protocole = getprotobyname("tcp");
	if (!protocole)
		ft_exit("NO FIND THE NAME OF PROTOCOLE : try \"TCP\"\n");
	ft_printf("[SERVER ✅i ] Creating server ... \n");
	sock = socket(PF_INET, SOCK_STREAM, protocole->p_proto);
	syn.sin_family = AF_INET;
	syn.sin_port = htons(port);
	syn.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&syn, sizeof(syn)) == -1)
		ft_exit("THIS PORT ARE USED BY ANOTHER PROGRAM TRY LATER \n");
	listen(sock, 42);
	ft_printf("[SERVER ✅i ] Server are create with success port : %d\n", port);
	return (sock);
}


void	parse_command(char *buffer, struct sockaddr_in syn, int cs, char *path)
{
	char	**split;

	split = ft_strsplit(buffer, ' ');
	if (split[0] && !ft_strcmp(split[0], "ls"))
	{
		if (split && split[1] && split[2])
			run_ls(syn, cs, split[1], split[2]);
		else if (split && split[1])
			run_ls(syn, cs, split[1], NULL);
		else
			run_simple_ls(syn, cs);
	}
	else if (split[0] && !ft_strcmp(split[0], "pwd"))
		run_pwd(syn, cs);
	else if (split[0] && (!ft_strcmp(split[0], "quit") || !ft_strcmp(split[0], "TERM42KO")))
		run_quit(syn, cs);
	else if (split[0] && !ft_strcmp(split[0], "cd"))
	{
		if (split && split[1])
			run_cd(syn, cs, path, split[1]);
		else
			run_cd_default(syn, cs, path);
	}
	else if (split[0] && !ft_strcmp(split[0], "get"))
	{
		if (split && split[1])
			run_get(syn, cs, path, split[1]);
		else
			run_get(syn, cs, path, NULL);
	}
	else
		send_unknow_message(cs);

}

void	create_client(int cs, struct sockaddr_in syn)
{
	pid_t					father;
	int						r;
	char					buffer[1024];
	char					path[3000];

	getcwd(path, 1024);
	ft_printf("Actual serveur path %s\n", path);
	father = fork();
	if (father == -1)
		ft_exit("FORK ERROR\n");
	else if (father == 0)
	{
		ft_printf("[SERVER ✅i ] Connection from %s - 🌐  USER_ID = %d \n",
				inet_ntoa(syn.sin_addr), cs);
		g_signal_fd = cs;
		signal_handler();
		while ((r = read(cs, buffer, 1023)) > 0)
		{
			buffer[r] = '\0';
			ft_printf("received %d bytes: [%s]\n", r, buffer);
			parse_command(buffer, syn, cs, path);
		}
	}
	close(cs);
}

int		main(int argc, char **argv)
{
	int						port;
	int						sock;
	int						cs;
	struct					sockaddr_in syn;
	unsigned int			synlen;

	ft_printf("\e[1;1H\e[2J");
	if (argc != 2 || ft_strcmp(ft_itoa(ft_atoi(argv[1])), argv[1]))
		usage(argv[0], 0);
	port = ft_atoi(argv[1]);
	if (port <= 0 || port > 65535)
		usage(argv[0], 1);
	sock = create_server(port);
	synlen = sizeof(syn);
	g_signal_fd = sock;
	signal_handler();
	while (1)
	{
		cs = accept(sock, (struct sockaddr*) &syn, &synlen);
		create_client(cs, syn);
	}
	close(sock);
	return (0);
}
