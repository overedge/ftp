/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:54:25 by nahmed-m          #+#    #+#             */
/*   Updated: 2017/05/09 14:04:18 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	usage(char *argv, char error)
{
	if (error == 0)
		ft_printf("%s <addr> <port>\n", argv);
	else
		ft_printf("%s <addr ipv4> <port [1 - 65535]> \n", argv);
	exit(EXIT_FAILURE);
}

void	ft_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
