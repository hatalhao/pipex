/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_variants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:15:04 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 14:21:40 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_struct(t_cmd *cmd)
{
	free_arr(cmd->args);
	free(cmd->path);
	free(cmd);
}

void	free_list(t_cmd **list)
{
	t_cmd	*iter;
	t_cmd	*tmp;

	if (!list)
		return ;
	iter = *list;
	while (iter)
	{
		tmp = iter;
		iter = iter->next;
		free_struct(tmp);
	}
	free(list);
	list = NULL;
}
