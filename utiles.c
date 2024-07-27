/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/07/27 00:43:10 by hamza            ###   ########.fr       */
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
		fprintf(stderr, "--------------------------\n");
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
		fprintf(stderr, "----------------- 12 -----------------\n");
		exit(0);
	}
	else
	{
		fprintf(stderr, "--------------------------------------\n");
		dup2(info->pipefd[0], info->keeper);
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

	dup2(info->keeper, 0);
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

	// char *buffer;
	// buffer = (char *) malloc (1000);
	// buffer [999] = 0;
	// fprintf(stderr, "access fd == %d\n", open(info->av[info->ac - 1], W_OK));
	// fprintf(stderr, "parent fd[1] == %d\n", info->fd[1]);
	// fprintf(stderr, "===> %zd\n", read(info->fd[1], buffer, 1));
	// fprintf(stderr,"--> %c\n", buffer[0]);
	// free (buffer);

}

void	executions(t_cmd **list, t_data *info)
{
	t_cmd	*tail;
	t_cmd	*iter;

	tail = last_node(*list);
	iter = *list;
	while (iter)
	{
		// if (pipe(pipefd2) == -1)
		// {
		// 	perror ("Pipe in executions failed\n");
		// 	return ;
		// }
		fprintf(stderr, "path -> %s\n", iter->path);
		if (iter == *list)
			file_to_pipe(info, iter);
		else if (iter == tail)
			pipe_to_file(info, iter);
		else
			pipe_to_pipe(info, iter);
		iter = iter->next;
	}
}

void	pipe_fork(t_cmd **list, t_data *info)
{
	t_cmd	*tail;
	t_cmd	*iter;
	int		keeper;

	keeper = info->fd[0];
	tail = last_node(*list);
	iter = *list;
	while (iter)
	{
		fprintf(stderr,"--==--\n");
		if (pipe(info->pipefd) == -1)
			return perror ("Pipe in pipe_fork() failed\n");
		if (iter == *list){
			dup2(keeper, 0);
			close (keeper);
		}
		else if (iter == tail){
			dup2(keeper, info->pipefd[0]);
			break ;
		}
		else {
			dup2(keeper, info->pipefd[0]);
			close (keeper);
		}
		dup2 (info->pipefd[0], keeper);
		close (info->pipefd[0]);
		close (info->pipefd[1]);
		iter = iter->next;
	}
}
