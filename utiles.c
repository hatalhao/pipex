/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/24 17:28:18 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	file_to_pipe(t_data *info, t_cmd *cmd)
{
	if (pipe(info->pfd) == -1)
	{
		perror("PIPE FAILED\n");
		return ;
	}
	info->pid = fork();
	if (info->pid == -1)
	{
		perror("FORK FAILED\n");
		return ;
	}
	if (!info->pid)
	{
		first_cmd(info->av, cmd, info);
		exit(0);
	}
	else
	{
		fprintf(stderr, "--------------------------\n");
		close(info->pfd[0]);
		close(info->pfd[1]);
	}
}

void	pipe_to_pipe(t_data *info, t_cmd *cmd)
{
	if (pipe(info->pfd) == -1)
	{
		perror("PIPE FAILED\n");
		return ;
	}
	info->pid = fork();
	if (info->pid == -1)
	{
		perror ("FORK FAILED\n");
		return ;
	}
	if (!info->pid)
	{
		mid_cmd(cmd, info);
		fprintf(stderr, "----------------- 12 -----------------\n");
		exit(0);
	}
	else
	{
		fprintf(stderr, "--------------------------------------\n");
		close(info->pfd[0]);
		close(info->pfd[1]);
		// waitpid(info->pid, NULL, 0);
		// wait(NULL);
	}
}

void	pipe_to_file(t_data *info, t_cmd *cmd)
{
	// char *buffer;
	// buffer = (char *) malloc (1000);
	// buffer [999] = 0;
	// fprintf(stderr, "===> %zd\n", read(info->pfd[0], buffer, 10));
	// fprintf(stderr,"--> %s\n", buffer);
	info->fd[1] = open(info->av[info->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (info->fd[1] == -1)
	{
		perror("Open Failed\n");
		return ;
	}
	if (pipe(info->pfd) == -1)
	{
		perror("PIPE FAILED\n");
		return ;
	}
	info->pid = fork();
	if (info->pid == -1)
	{
		perror("FORK FAILED\n");
		return ;
	}
	if (!info->pid)
	{
		last_cmd(cmd, info);
		close (info->fd[1]);
		exit(0);
	}
	else
	{
		close(info->pfd[0]);
		close (info->pfd[1]);
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
	t_cmd	*head;
	t_cmd	*tail;
	t_cmd	*iter;
	int		pfd2[2];

	head = *list;
	tail = last_node(*list);
	iter = *list;
	while (iter)
	{
		if (pipe(pfd2) == -1)
		{
			perror ("Pipe in executions failed\n");
			return ;
		}
		fprintf(stderr, "path -> %s\n", iter->path);
		if (iter == head)
			file_to_pipe(info, iter);
		else if (iter == tail)
			pipe_to_file(info, iter);
		else
			pipe_to_pipe(info, iter);
		iter = iter->next;
	}
}
