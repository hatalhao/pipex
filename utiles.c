/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/07/30 18:16:21 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	error_exit(char *str)
{
	fprintf(stderr, "Error in %s", str);
	exit(1);	
}

void file_to_pipe(t_data *info, t_cmd *cmd)
{
	if (pipe(info->pipefd) == -1)
		error_exit("pipe");
	info->pid = fork();
	if (info->pid == -1)
		error_exit("fork");
	if (info->pid == 0)
	{
		close(info->pipefd[0]);
		if (dup2(info->infile, STDIN) == -1 || dup2(info->pipefd[1], STDOUT) == -1)
			error_exit("dup2");
		close(info->infile);
		close(info->pipefd[1]);
		execve(cmd->path, cmd->args, NULL);
		error_exit("execve");
	}
	close(info->pipefd[1]);
	close(info->infile);
	info->keeper = info->pipefd[0];
}

void pipe_to_pipe(t_data *info, t_cmd *cmd)
{
	if (pipe(info->pipefd) == -1)
		error_exit("pipe");
	info->pid = fork();
	if (info->pid == -1)
		error_exit("fork");
	if (info->pid == 0)
	{
		close(info->pipefd[0]);
		if (dup2(info->keeper, STDIN) == -1 || dup2(info->pipefd[1], STDOUT) == -1)
			error_exit("dup2");
		close(info->keeper);
		close(info->pipefd[1]);	
		execve(cmd->path, cmd->args, NULL);
			error_exit("execve");
	}
	close(info->pipefd[1]);
	close(info->keeper);
	info->keeper = info->pipefd[0];
}

void pipe_to_file(t_data *info, t_cmd *cmd)
{
	info->pid = fork();
	if (info->pid == -1)
		error_exit("fork");
	if (info->pid == 0)
	{
		if (dup2(info->keeper, STDIN) == -1 || dup2(info->outfile, STDOUT) == -1)
			error_exit("dup2");
		
		close(info->keeper);
		close(info->outfile);	
		execve(cmd->path, cmd->args, NULL);
			error_exit("execve");

	}
	close(info->keeper);
	close(info->outfile);
}

void executions(t_cmd **list, t_data *info)
{
	t_cmd	*tail;
	t_cmd	*iter;
	int 	index;
	
	index = 0;
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
	while (index < info->ac - 3)
	{
		waitpid(info->pid, NULL, 0);
		index++;
	}
}
