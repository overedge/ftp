#include "serveur.h"


void	catchme(int signal)
{
	ft_printf("[SERVER 🅾️i] the signal %d catched .. Exit ..\n", signal);
	close(g_signal_fd);
	exit(EXIT_FAILURE);
}


void	signal_handler(void)
{
	signal(SIGINT, catchme);
}
