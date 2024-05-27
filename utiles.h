/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 21:40:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/05/12 21:48:51 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILES_H
#define UTILES_H

# include <stdio.h>
# include <unistd.h>
# include <unistd.h>

void	ft_malloc(void	*ptr, int size, int data_size);
void	ft_free(t_node	*node);


typedef	struct		s_node
{
	void			*allocated;
	struct	s_node	*next;
	struct	s_node	*prev;
}					t_node;

typedef	struct s_list
{
	void	
};


#endif