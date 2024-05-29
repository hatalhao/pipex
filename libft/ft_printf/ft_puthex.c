/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:26:03 by hatalhao          #+#    #+#             */
/*   Updated: 2023/12/06 20:09:04 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(unsigned long l, int *c)
{
	if (l >= 16)
		ft_puthex(l / 16, c);
	ft_putchar("0123456789abcdef"[l % 16], c);
}