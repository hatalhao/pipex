/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:27:55 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 17:44:04 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*		Return the last node of a linked list	*/
t_cmd	*last_node(t_cmd *list)
{
	if (!list)
		return (NULL);
	while (list)
	{
		if (!list->next)
			return (list);
		list = list->next;
	}
	return (list);
}

/*		Allocate memory for a node and fill its variables	*/
t_cmd	*make_node(t_data *info, char *av)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = get_args(av);
	new->path = extract_path(info->paths, new);
	if (!new->path)
	{
		close (info->infile);
		close (info->outfile);
		free_arr(new->args);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}
