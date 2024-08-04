/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:36:24 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/04 04:36:25 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd, int to_free);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_join(char *s1, char *s2);
char	*ft_duplicate(char const *src);
size_t	ft_length(char const *str);
void	*ft_copy(void *dest, void const *src, size_t n);
void	ft_free(char **str);

#endif