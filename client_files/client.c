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
	if (!ft_strcmp(addr, "localhost"))
			addr = "127.0.0.1";
	syn.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&syn, sizeof(syn)) == -1)
		ft_exit("CHECK YOU CONNECTION OR YOU FIREWALL PARAMETERS\n");
	return (sock);
}

void	get_file(int sock, unsigned int size, char *line)
{
	char			**split;
	int				fd;
	unsigned int	count;
	unsigned int	tmp;

	char			*message;
	char			data[300000];

	count = 0;
	message = "\033[31;1;4;5;7m This file existe in you filesystem🚫 \033[0m";
	split = ft_strsplit(line, ' ');

	ft_bzero(data,300000);
	if (split && split[1])
	{
		ft_printf("this file : %s\n", split[1]);
		fd = open(split[1], O_WRONLY | O_CREAT | O_EXCL, S_IRWXU);
		if (fd < 0)
		{
			send(sock, "KO", ft_strlen("KO"), 0);
			ft_printf("%s\n", message);
		}
		else
		{
			send(sock, "KO", ft_strlen("OK"), 0);
			while (count < size)
			{
				ft_bzero(data,300000);
				ft_printf("izi\n");
				tmp = recv(sock, data, 300000, 0);
				write(fd, data, tmp);
				count += tmp;
			}
			close(fd);
			ft_printf("FILE ARE SUCCESS DOWNLOAD ✅  \n");
		}
	}
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
	//ft_printf("Line = %d | line = %s\n", ft_strlen(line), line);
	if (ft_strlen(line) > 0)
		recv(sock, data, 300000, 0);
	if (data[0] && data[0] == '|' && data[1] && data[1] == '#' && data[2])
	{
	//	printf("the size is %u\n", ft_atoi(&data[2]));
		get_file(sock, ft_atoi(&data[2]), line);
	}
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

