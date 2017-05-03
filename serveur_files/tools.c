#include "serveur.h"

void	send_unknow_message(int sock)
{
	char *message = "\033[31;1;4;5;7mBad Cli\n\033[0m";

	send(sock, message, ft_strlen(message), 0);
}

void	ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	usage(char *argv, char error)
{
	if (error == 0)
		ft_printf("%s <port>\n", argv);
	else
		ft_printf("%s <port [1 - 65535]> \n", argv);
	exit(EXIT_FAILURE);
}
