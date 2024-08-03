/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 02:29:39 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/03 06:51:12 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	executions_heredoc(t_cmd *list, t_data *info)
{
	t_cmd	*tail;
	t_cmd	*iter;
	int 	index;
	pid_t	*pids;
	
	
	index = 0;
	tail = last_node(list);
	iter = list;
	fprintf(stderr, "ac %d \t non_cmd %d\n", info->ac, info->non_cmd);
	pids = (int *) malloc (sizeof(int) * (info->ac - info->non_cmd));
	while (iter)
	{
		if (iter == list)
			file_to_pipe(info, iter);
		else if (iter == tail)
			pipe_to_file(info, iter);
		else
			pipe_to_pipe(info, iter);
		pids[index++] = info->pid;
		iter = iter->next;
	}
	index = 0;
	while (index < info->ac - info->non_cmd)
		waitpid(pids[index++], NULL, 0);
	free (pids);
}
