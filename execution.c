/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/03 02:47:08 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	error_exit(char *str)
{
	ft_putstr_fd("Error in ", 2);
	ft_putstr_fd(str, 2);
	exit(1);	
}

void file_to_pipe(t_data *info, t_cmd *cmd)
{
	if (pipe(info->pipefd) == -1)
		error_exit("pipe\n");
	info->pid = fork();
	if (info->pid == -1)
		error_exit("fork\n");
	if (info->pid == 0)
	{
		close(info->pipefd[0]);
		if (dup2(info->infile, STDIN) == -1 || dup2(info->pipefd[1], STDOUT) == -1)
			error_exit("dup2\n");
		close(info->infile);
		close(info->pipefd[1]);
		execve(cmd->path, cmd->args, NULL);
		error_exit("execve\n");
	}
	close(info->pipefd[1]);
	close(info->infile);
	info->keeper = info->pipefd[0];
}

void pipe_to_pipe(t_data *info, t_cmd *cmd)
{
	if (pipe(info->pipefd) == -1)
		error_exit("pipe\n");
	info->pid = fork();
	if (info->pid == -1)
		error_exit("fork\n");
	if (info->pid == 0)
	{
		close(info->pipefd[0]);
		if (dup2(info->keeper, STDIN) == -1 || dup2(info->pipefd[1], STDOUT) == -1)
			error_exit("dup2\n");
		close(info->keeper);
		close(info->pipefd[1]);
		execve(cmd->path, cmd->args, NULL);
			error_exit("execve\n");
	}
	close(info->pipefd[1]);
	close(info->keeper);
	info->keeper = info->pipefd[0];
}

void pipe_to_file(t_data *info, t_cmd *cmd)
{
	info->pid = fork();
	if (info->pid == -1)
		error_exit("fork\n");
	if (info->pid == 0)
	{
		if (dup2(info->keeper, STDIN) == -1 || dup2(info->outfile, STDOUT) == -1)
			error_exit("dup2 - keeper\n");
		close(info->keeper);
		close(info->outfile);	
		execve(cmd->path, cmd->args, NULL);
			error_exit("execve\n");
	}
	close(info->keeper);
	close(info->outfile);
}

void executions(t_cmd *list, t_data *info)
{
	t_cmd	*tail;
	t_cmd	*iter;
	int 	index;
	pid_t	*pids;
	
	
	index = 0;
	tail = last_node(list);
	iter = list;
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
