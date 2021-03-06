/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:50:53 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/09 13:50:57 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
