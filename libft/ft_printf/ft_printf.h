/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:28 by hatalhao          #+#    #+#             */
/*   Updated: 2023/12/06 14:33:44 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

int		ft_printf(char const	*str, ...);

void	ft_spf(char spf, va_list args, int *l);
void	ft_unsigned(unsigned int nb, int *c);
void	ft_putchex(unsigned int l, int *c);
void	ft_puthex(unsigned long l, int *c);
void	ft_putptr(unsigned long l, int *c);
void	ft_putstr(char *str, int *c);
void	ft_putchar(char ch, int *c);
void	ft_putnbr(long nb, int *c);

#endif