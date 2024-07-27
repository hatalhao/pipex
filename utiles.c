/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/07/27 06:50:59 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	file_to_pipe(t_data *info, t_cmd *cmd)
{
	if (pipe(info->pipefd) == -1)
		return (perror("PIPE FAILED\n"));
	info->pid = fork();
	if (info->pid == -1)
		return perror("FORK FAILED\n");
	if (!info->pid)
	{
		first_cmd(cmd, info);
		exit(0);
	}
	else
	{
		if (dup2(info->pipefd[0], info->keeper) == -1)
			return (perror("dup2 in file_to_pipe failed\n"));
		close(info->pipefd[0]);
		close(info->pipefd[1]);
	}
}

void	pipe_to_pipe(t_data *info, t_cmd *cmd)
{
	if (pipe(info->pipefd) == -1)
		return perror("PIPE FAILED\n");
	if (dup2(info->keeper, 0) == -1)
		return (perror("dup2 in file_to_pipe failed\n"));
	info->pid = fork();
	if (info->pid == -1)
		return (perror ("FORK FAILED\n"));
	if (!info->pid)
	{
		mid_cmd(cmd, info);
		exit(0);
	}
	else
	{
		if (dup2(info->pipefd[0], info->keeper) == -1)
			return (perror("DUP2 FAILED\n"));
		close(info->pipefd[0]);
		close(info->pipefd[1]);
	}
}

void	pipe_to_file(t_data *info, t_cmd *cmd)
{
	if (pipe(info->pipefd) == -1)
		return (perror("PIPE FAILED\n"));
	info->pid = fork();
	if (info->pid == -1)
		return (perror("FORK FAILED\n"));
	if (dup2(info->pipefd[0], info->keeper) == -1)
		return (perror("DUP2 FAILED\n"));
	if (!info->pid)
	{
		last_cmd(cmd, info);
		close (info->fd[1]);
		exit(0);
	}
	else
	{
		close(info->pipefd[0]);
		close (info->pipefd[1]);
		close (info->fd[1]);
		// wait(NULL);
		// waitpid(info->pid, NULL, 0);
	}
}

void	executions(t_cmd **list, t_data *info)
{
	t_cmd	*tail;
	t_cmd	*iter;

	tail = last_node(*list);
	iter = *list;
	while (iter)
	{
		if (iter == *list)
			file_to_pipe(info, iter);
		else if (iter == tail)
			pipe_to_file(info, iter);
		else
			pipe_to_pipe(info, iter);
		iter = iter->next;
	}
}
