/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:25:48 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 17:49:56 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*		Print the error message assigned to the errno set		*/
void	error_exit(void)
{
	char	*str;

	str = strerror(errno);
	ft_putstr_fd(str, 2);
	exit(1);
}

/*		Create a child process and execute the necessary ops	*/
void	file_to_pipe(t_data *info, t_cmd *cmd, t_cmd **list)
{
	if (pipe(info->pipefd) == -1)
		error_exit();
	info->pid = fork();
	if (info->pid == -1)
		error_exit();
	if (info->pid == 0)
	{
		close(info->pipefd[0]);
		if (dup2(info->infile, STDIN) == -1 || \
		dup2(info->pipefd[1], STDOUT) == -1)
			error_exit();
		close(info->infile);
		close(info->pipefd[1]);
		if (execve(cmd->path, cmd->args, NULL) == -1)
		{
			final_curtain(list, info, (info->limiter != NULL));
			error_exit();
		}
	}
	close(info->pipefd[1]);
	close(info->infile);
	info->keeper = info->pipefd[0];
}

/*		Create a child process and execute the necessary ops	*/
void	pipe_to_pipe(t_data *info, t_cmd *cmd, t_cmd **list)
{
	if (pipe(info->pipefd) == -1)
		error_exit();
	info->pid = fork();
	if (info->pid == -1)
		error_exit();
	if (info->pid == 0)
	{
		close(info->pipefd[0]);
		if (dup2(info->keeper, STDIN) == -1 || \
		dup2(info->pipefd[1], STDOUT) == -1)
			error_exit();
		close(info->keeper);
		close(info->pipefd[1]);
		if (execve(cmd->path, cmd->args, NULL) == -1)
		{
			final_curtain(list, info, (info->limiter != NULL));
			error_exit();
		}
	}
	close(info->pipefd[1]);
	close(info->keeper);
	info->keeper = info->pipefd[0];
}

/*		Create a child process and execute the necessary ops	*/
void	pipe_to_file(t_data *info, t_cmd *cmd, t_cmd **list)
{
	info->pid = fork();
	if (info->pid == -1)
		error_exit();
	if (info->pid == 0)
	{
		if (dup2(info->keeper, STDIN) == -1 || \
		dup2(info->outfile, STDOUT) == -1)
			error_exit();
		close(info->keeper);
		close(info->outfile);
		if (execve(cmd->path, cmd->args, NULL) == -1)
		{
			final_curtain(list, info, (info->limiter != NULL));
			error_exit();
		}
	}
	close(info->keeper);
	close(info->outfile);
}

/*		Manage the execution of the program		*/
void	executions(t_cmd **list, t_data *info)
{
	t_cmd	*tail;
	t_cmd	*iter;
	int		index;

	index = 0;
	tail = last_node(*list);
	iter = *list;
	info->pids = (int *) malloc(sizeof(int) * (info->ac - info->non_cmd));
	while (iter)
	{
		if (iter == *list)
			file_to_pipe(info, iter, list);
		else if (iter == tail)
			pipe_to_file(info, iter, list);
		else
			pipe_to_pipe(info, iter, list);
		info->pids[index++] = info->pid;
		iter = iter->next;
	}
	index = 0;
	while (index < info->ac - info->non_cmd)
		waitpid(info->pids[index++], &info->exit_status, 0);
	free (info->pids);
}
