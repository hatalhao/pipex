/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:36:17 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/04 04:36:18 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **str)
{
	free(*str);
	*str = 0;
}

int	new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*the_line(char *total, char **line)
{
	size_t	len;
	char	*remainder;

	len = 0;
	remainder = 0;
	if (total)
	{
		while (total[len] && total[len] != '\n')
			len++;
		len += (total[len] == '\n');
		if (len)
		{
			*line = ft_substr(total, 0, len);
			remainder = ft_substr(total, len, ft_length(total) - len + 1);
		}
	}
	return (remainder);
}

char	*ft_read(int fd)
{
	char	*str;
	char	*tmp;
	long	rd;

	str = 0;
	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	rd = 1;
	while (rd)
	{
		rd = read(fd, tmp, BUFFER_SIZE);
		if (rd == -1)
		{
			ft_free(&str);
			break ;
		}
		tmp[rd] = '\0';
		str = ft_join(str, ft_duplicate(tmp));
		if (new_line(tmp) >= 0)
			break ;
	}
	ft_free(&tmp);
	return (str);
}

char	*get_next_line(int fd, int to_free)
{
	static char	*remainder;
	char		*total;
	char		*line;
	char		*tmp;

	line = 0;
	tmp = 0;
	total = 0;
	if (fd < 0 || (read (fd, total, 0) == -1)
		|| BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || to_free)
	{
		ft_free(&remainder);
		return (NULL);
	}
	if (remainder)
		total = ft_join(remainder, 0);
	tmp = ft_read(fd);
	if (tmp)
	{
		total = ft_join(total, tmp);
		remainder = the_line(total, &line);
	}
	ft_free(&total);
	return (line);
}
