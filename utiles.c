/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/07/28 22:50:48 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	_____tester(int pipefd, int size)
{
	char arr[size];
	arr[size - 1] = 0;
	int rv = read(pipefd, arr, size - 1); 
	if (rv == -1)
		return (perror("Read Failed the _____Tester\n"));
	fprintf(stderr, "rv = %d; arr = %s\n", rv, arr);
}

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
		waitpid(info->pid, NULL, 0);
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
	if (dup2(info->keeper, info->pipefd[0]) == -1)
		return (perror("dup2 in pipe_to_pipe failed\n"));

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
		if (waitpid(info->pid, NULL, 0) == -1)
			return (perror("Waitpid in pipe_to_pipe failed\n"));
		_____tester(info->pipefd[0], 180);
		if (dup2(info->pipefd[0], info->keeper) == -1)
			return (perror("DUP2 FAILED\n"));
		// sleep(100);
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
	if (dup2(info->keeper, info->pipefd[0]) == -1)
		return (perror("DUP2 FAILED\n"));
	if (!info->pid)
	{
		last_cmd(cmd, info);
		close (info->outfile);
		exit(0);
	}
	else
	{
		waitpid(info->pid, NULL, 0);
		close(info->pipefd[0]);
		close (info->pipefd[1]);
		close (info->outfile);
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
