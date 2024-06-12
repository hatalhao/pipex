/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/10 21:47:32 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	file_to_pipe(t_data *info, t_cmd *cmd)
{
	pipe(info->pfd);
	info->pid = fork();
	if (!info->pid)
		first_cmd(info->av, cmd, info);
	close (info->pfd[0]);
	dup2(info->pfd[1], 1);
	close (info->pfd[1]);
	printf("HERE %s\n", __func__);
	waitpid(info->pid, NULL, 0);
	// info->pid++;
}

void	pipe_to_pipe(t_data *info, t_cmd *cmd)
{
	pipe(info->pfd);
	info->pid = fork();
	if (!info->pid)
		mid_cmd(cmd, info);
	close (info->pfd[0]);
	dup2(info->pfd[1], 1);
	close (info->pfd[1]);
	waitpid(info->pid, NULL, 0);
	printf("HERE %s\n", __func__);
}

void	pipe_to_file(t_data *info, t_cmd *cmd)
{
	pipe(info->pfd);
	info->pid = fork();
	if (!info->pid)
		last_cmd(info->av, cmd, info);
	printf("HERE %s\n", __func__);
	waitpid(info->pid, NULL, 0);
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
		printf("path -> %s\n", iter->path);
		if (iter == head)
			file_to_pipe (info, iter);
		else if (iter == tail)
			pipe_to_file(info, iter);
		else
			pipe_to_pipe (info, iter);
		// waitpid(-1, NULL, 0);
		printf("---------> %d\n", info->pid);
		info->pid = 12;
		iter = iter->next;
	}
}
