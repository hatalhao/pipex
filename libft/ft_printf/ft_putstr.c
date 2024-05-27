/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:26:31 by hatalhao          #+#    #+#             */
/*   Updated: 2023/12/06 14:26:34 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str, int *c)
{
	if (!str)
	{
		ft_putstr("(null)", c);
		return ;
	}
	while (*str)
	{
		ft_putchar(*str, c);
		str++;
	}
}
