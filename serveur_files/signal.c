#include "serveur.h"


void	catchme(int signal)
{
	ft_printf("[SERVER 🅾️i] the signal %d catched .. Exit ..\n", signal);
	exit(EXIT_FAILURE);
}


void	signal_handler(void)
{
	int		i;

	i = 1;
	while (i < 32)
	{
		signal(i, catchme);
		i++;
	}
}
