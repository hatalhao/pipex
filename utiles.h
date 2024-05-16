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

void	ft_malloc(void	*ptr);
void	ft_free(void	*ptr);


typedef	struct		s_node
{
	void			*allocated;
	struct	s_node	*next;
	struct	s_node	*prev;
}					t_node;

#endif