/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:27:07 by hatalhao          #+#    #+#             */
/*   Updated: 2023/12/06 14:51:10 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_spf(char spf, va_list args, int *l)
{
	if (spf == 's')
		ft_putstr(va_arg(args, char *), l);
	else if (spf == 'c')
		ft_putchar(va_arg(args, int), l);
	else if (spf == 'd')
		ft_putnbr(va_arg(args, int), l);
	else if (spf == 'i')
		ft_putnbr(va_arg(args, int), l);
	else if (spf == 'u')
		ft_unsigned(va_arg(args, unsigned int), l);
	else if (spf == 'x')
		ft_puthex(va_arg(args, unsigned int), l);
	else if (spf == 'X')
		ft_putchex(va_arg(args, unsigned int), l);
	else if (spf == 'p')
		ft_putptr(va_arg(args, unsigned long), l);
	else
		ft_putchar(spf, l);
}
