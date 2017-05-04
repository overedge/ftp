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

void	run_ls(struct sockaddr_in syn, int cs)
{
	pid_t	father;
	char *const parmList[] = {"/bin/ls", NULL};

	ft_printf("[SERVER 📶  received ls fron %s\n", inet_ntoa(syn.sin_addr));
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

void	run_pwd(struct sockaddr_in syn, int cs)
{
	pid_t	father;
	char *const parmList[] = {"/bin/pwd", NULL};

	ft_printf("[SERVER 📶  received pwd fron %s\n", inet_ntoa(syn.sin_addr));
	father = fork();
	if (father == -1)
		ft_exit("FORk ERROR\n");
	else if (father == 0)
	{
		dup2(cs, 1);
		execv("/bin/pwd", parmList);
	}
	else 
		wait(&father);
}
