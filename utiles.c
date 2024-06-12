/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/12 20:23:08 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	file_to_pipe(t_data *info, t_cmd *cmd)
{
	int m = 9;
	pipe(info->pfd);
	info->pid = fork();
	fprintf(stderr, "-------> %d\n", info->pid);
	if (!info->pid)
	{
		first_cmd(info->av, cmd, info);
		m = waitpid(info->pid, NULL, 0);
	}// else
		// printf("ERROR HERE %s\n", __func__);
	close(info->pfd[0]);
	dup2(info->pfd[1], 1);
	// printf("HERE %s\n", __func__);
	close(info->pfd[1]);
	fprintf(stderr, "======+> %d\n", m);
}

void	pipe_to_pipe(t_data *info, t_cmd *cmd)
{
	printf("HERE %s\n", __func__);
	pipe(info->pfd);
	info->pid = fork();
	if (!info->pid)
		mid_cmd(cmd, info);
	// else
	// 	printf("ERROR HERE %s\n", __func__);
	close(info->pfd[0]);
	dup2(info->pfd[1], 1);
	close(info->pfd[1]);
	waitpid(info->pid, NULL, 0);
}

void	pipe_to_file(t_data *info, t_cmd *cmd)
{
	fprintf(stderr, "HERE %s\n", __func__);
	pipe(info->pfd);
	info->pid = fork();
	if (!info->pid)
	{
		last_cmd(info->av, cmd, info);
		waitpid(info->pid, NULL, 0);
	}// else
	// 	printf("ERROR HERE %s\n", __func__);
}

void	executions(t_cmd **list, t_data *info)
{
	t_cmd *head;
	t_cmd *tail;
	t_cmd *iter;

	head = *list;
	fprintf(stderr, "&iter == %p\n", head);
	tail = last_node(*list);
	iter = *list;
	fprintf(stderr, "&iter == %p\n", *list);
	while (iter)
	{
		printf("path -> %s\n", iter->path);
		if (iter == head)
		{
			fprintf(stderr, "iter == head\n");
			file_to_pipe(info, iter);
		}
		else if (iter == tail)
		{
			fprintf(stderr, "iter == tail\n");	
			pipe_to_file(info, iter);
		}
		else
			pipe_to_pipe(info, iter);
		// waitpid(-1, NULL, 0);
		printf("---------> %d\n", info->pid);
		// info->pid = 12;
		iter = iter->next;
		write (2, "HERE\n", 5);
	}
}
