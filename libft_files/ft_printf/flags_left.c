/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_left.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahmed-m <nahmed-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 20:24:36 by nahmed-m          #+#    #+#             */
/*   Updated: 2016/01/21 00:46:22 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flags_left(char *fmt, t_var *e)
{
	if (fmt[e->i] == '-' && fmt[e->i + 1] == '\0')
		e->error = 1;
	else if (fmt[e->i] == '-')
	{
		e->f_left = 1;
		e->i++;
	}
	else
		e->f_left = 0;
}
