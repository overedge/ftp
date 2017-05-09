/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:54:20 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/09 13:55:36 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*protocole;
	struct sockaddr_in	syn;

	protocole = getprotobyname("tcp");
	if (!protocole)
		ft_exit("NO FIND THE NAME OF PROTOCOLE : try \"TCP\"\n");
	sock = socket(PF_INET, SOCK_STREAM, protocole->p_proto);
	syn.sin_family = AF_INET;
	syn.sin_port = htons(port);
	if (!ft_strcmp(addr, "localhost"))
		addr = "127.0.0.1";
	syn.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&syn, sizeof(syn)) == -1)
		ft_exit("CHECK YOU CONNECTION OR YOU FIREWALL PARAMETERS\n");
	return (sock);
}

void	parse_inputs(int sock)
{
	char			*line;
	char			data[300000];

	ft_printf("🗂i ftp > ");
	get_next_line(1, &line);
	if (!ft_strcmp("quit", line))
	{
		ft_printf("Closing the connection...\n");
		send(g_actual_socket, "TERM42KO", 8, 0);
		close(sock);
		exit(EXIT_SUCCESS);
	}
	send(sock, line, ft_strlen(line), 0);
	ft_bzero(data, 300000);
	if (ft_strlen(line) > 0)
		recv(sock, data, 300000, 0);
	if (data[0] && data[0] == '|' && data[1] && data[1] == '#' && data[2])
		get_file(sock, ft_atoi(&data[2]), line);
	else if (data[1] && !ft_strcmp("OK", data))
		put_file(sock, line);
	else
		ft_printf("%s\n", data);
}

void	catchme(int signal)
{
	ft_printf("Closing the connection... \n", signal);
	send(g_actual_socket, "TERM42KO", 8, 0);
	close(g_actual_socket);
	exit(EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	int						port;
	int						sock;

	ft_printf("\e[1;1H\e[2J");
	if (argc != 3 || ft_strcmp(ft_itoa(ft_atoi(argv[2])), argv[2]))
		usage(argv[0], 0);
	port = ft_atoi(argv[2]);
	if (port <= 0 || port > 65535)
		usage(argv[0], 1);
	ft_printf("Connecting to server...\n");
	sock = create_client(argv[1], port);
	ft_printf("Connected\n");
	g_actual_socket = sock;
	signal(SIGINT, catchme);
	while (1)
		parse_inputs(sock);
	ft_putstr_fd("Connection on serveur was canceled !\n", 2);
	return (EXIT_FAILURE);
}
