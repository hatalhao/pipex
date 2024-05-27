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

void	ft_add_back(t_node **list, t_node *new)
{
	if (!list || !*list)
		*list = new;
	else
	{
		new->next = *list;
		
	}
	new->prev = NULL;
}

t_node	*new_addr(void	*ptr)
{
	t_node	*curr;

	curr->allocated = ptr;
	curr->next = NULL;
}

void	free_node(t_node	*node)
{
	t_node *tmp;

	tmp = ;
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

void	ft_malloc(t_node **list, void **ptr, int size, int data_size)
{
	*ptr = malloc ((size + 1) * data_size);
	if (!*ptr)
		return ;
	ft_add_back(list, new_addr(*ptr));
}

