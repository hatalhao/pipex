/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 00:07:46 by hatalhao          #+#    #+#             */
/*   Updated: 2024/04/19 17:22:36 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_length(char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_copy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (dest == src)
		return (dest);
	str1 = (unsigned char *)src;
	str2 = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		str2[i] = str1[i];
		i++;
	}
	return (dest);
}

char	*ft_join(char *s1, char *s2)
{
	size_t	i;
	char	*str;
	char	*ptr;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc((ft_length(s1) + ft_length(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ptr = str;
	if (s1)
		while (s1[i])
			*(str++) = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			*(str++) = s2[i++];
	*str = '\0';
	ft_free(&s1);
	ft_free(&s2);
	return (ptr);
}

char	*ft_duplicate(char const *src)
{
	size_t	i;
	char	*duplicate;

	if (!src)
		return (NULL);
	duplicate = (char *)malloc((ft_length(src) + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (src[i])
	{
		duplicate[i] = src[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;

	if (!s)
		return (0);
	ss = (char *)malloc((len + 1) * sizeof(char));
	if (ss == NULL)
		return (NULL);
	ft_copy(ss, s + start, len);
	ss[len] = '\0';
	return (ss);
}
