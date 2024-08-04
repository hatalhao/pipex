/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:35:28 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/04 04:35:29 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t		counter;
	int			in_word;
	char const	*p;

	if (s == NULL)
		return (0);
	counter = 0;
	in_word = 0;
	p = s;
	while (*p)
	{
		if (*p == c)
			in_word = 0;
		else if (in_word == 0)
		{
			counter++;
			in_word = 1;
		}
		p++;
	}
	return (counter);
}

static char	**free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static char	**str_all_fill(char **str, char const *s, char c)
{
	const char	*start;
	int			i;
	int			len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			len = s - start;
			str[i] = (char *)malloc((len + 1) * sizeof(char));
			if (!str[i])
				return (free_all(str));
			ft_memcpy(str[i], start, len);
			str[i][len] = '\0';
			i++;
		}
		else
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (0);
	str = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (str_all_fill(str, s, c));
}
