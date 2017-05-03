#include "client.h"

void	usage(char *argv, char error)
{
	if (error == 0)
		ft_printf("%s <add> <port>\n", argv);
	else
		ft_printf("%s <addr ipv4> <port [1 - 65535]> \n", argv);
	exit(EXIT_FAILURE);
}

void	ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}


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
	syn.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&syn, sizeof(syn)) == -1)
		ft_exit("CHECK YOU CONNECTION OR YOU FIREWALL PARAMETERS\n");
	return (sock);
}

void	parse_inputs(int sock)
{
	char	*line;
	char	data[20000];

	ft_printf("🗂i ftp > ");
	get_next_line(1, &line);
	if (!ft_strcmp("quit", line))
	{
		ft_printf("Closing the connection...\n");
		close(sock);
		exit(EXIT_SUCCESS);
	}
	send(sock, line, ft_strlen(line), 0);
	ft_bzero(data, 20000);
	if (ft_strlen(line) > 0)
		recv(sock, data, 20000, 0);
	ft_printf("%s\n", data);
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
	while (1)
		parse_inputs(sock);
	return (0);
}