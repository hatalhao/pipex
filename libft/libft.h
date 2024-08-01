/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:25 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/01 00:33:51 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <fcntl.h>
# include <errno.h>
# include "ft_printf/ft_printf.h"
# include "gnl/get_next_line.h"

void	ft_putstr_fd(char *s, int fd);
void	*ft_memcpy(void *dest, void const *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
