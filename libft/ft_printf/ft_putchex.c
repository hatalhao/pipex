/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:55 by hatalhao          #+#    #+#             */
/*   Updated: 2023/12/06 14:25:57 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchex(unsigned int l, int *c)
{
	if (l >= 16)
		ft_putchex(l / 16, c);
	ft_putchar("0123456789ABCDEF"[l % 16], c);
}
