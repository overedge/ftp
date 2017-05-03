#include "serveur.h"

int		create_server(int port)
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
	syn.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&syn, sizeof(syn)) == -1)
		ft_exit("THIS PORT ARE USED BY ANOTHER PROGRAM TRY LATER \n");
	listen(sock, 42);
	return (sock);
}

int		main(int argc, char **argv)
{
	int						port;
	int						sock;
	int						cs;
	struct		sockaddr_in syn;
	unsigned int			synlen;
	int						r;
	char					buffer[1024];
	pid_t					father;
	char *const parmList[] = {"/bin/ls", "-l", NULL};

	ft_printf("\e[1;1H\e[2J");
	if (argc != 2 || ft_strcmp(ft_itoa(ft_atoi(argv[1])), argv[1]))
		usage(argv[0], 0);
	port = ft_atoi(argv[1]);
	if (port <= 0 || port > 65535)
		usage(argv[0], 1);
	sock = create_server(port);
	//signal_handler();
	while (1)
	{
		cs = accept(sock, (struct sockaddr*) &syn, &synlen);
		father = fork();
		if (father == -1)
			ft_exit("FORK ERROR\n");
		else if (father == 0)
		{
			ft_printf("[SERVER ✅i ] Reveived a connection from %s\n", inet_ntoa(syn.sin_addr));
			while ((r = read(cs, buffer, 1023)) > 0)
			{
				buffer[r] = '\0';
				ft_printf("received %d bytes: [%s]\n", r, buffer);
				if (!ft_strcmp(buffer, "ls"))
				{
					ft_printf("[SERVER ✅  ] received ls from %s\n", inet_ntoa(syn.sin_addr));
					father = fork();
					if (father == -1)
						ft_exit("FORk ERROR\n");
					else if (father == 0)
					{
						dup2(cs, 1);
						execv("/bin/ls", parmList);
					}
					else 
						wait(&father);
				}
				else
					send_unknow_message(cs);
			}
		}
	}
	close(cs);
	close(sock);
	return (0);
}
