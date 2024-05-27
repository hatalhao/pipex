/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:06 by hatalhao          #+#    #+#             */
/*   Updated: 2023/12/06 20:21:44 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char const *str, ...)
{
	int		l;
	va_list	args;

	l = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			ft_spf(*(str + 1), args, &l);
			str++;
		}
		else if (*str != '%')
			ft_putchar(*str, &l);
		str++;
	}
	va_end(args);
	return (l);
}
