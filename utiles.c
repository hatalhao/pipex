/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/09 23:59:21 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	file_to_pipe(t_data *info, t_cmd *cmd)
{
	pipe(info->pfd);
	info->pid = fork();
	if (!info->pid)
		first_cmd(info->av, cmd, info->fd, info->pfd);
}

void	file_to_pipe()
{
	
}

void	executions(t_cmd **list, t_data *info)
{
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*iter;

	head = *list;
	tail = last_node(*list); 
	iter = *list;
	while (iter)
	{
		if (iter == head)
			file_to_pipe (info, iter);
		else if (iter == tail)
			pipe_to_file(info, iter);
		else
			pipe_to_pipe (info, iter);
	}
}