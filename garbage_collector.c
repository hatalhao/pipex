/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:40:33 by hatalhao          #+#    #+#             */
/*   Updated: 2024/05/12 21:49:18 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utiles.h"

void	free_node(void	*ptr)
{
	
}

void	ft_free(t_node	*ptr)
{
	t_node	*tmp;
	
	tmp = NULL;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		free (tmp);
	}
}

void	ft_malloc(void	*ptr)
{
	
}

