/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:08:30 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/13 02:01:01 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	file_to_pipe(t_data *info, t_cmd *cmd)
{

	pipe(info->pfd);
	info->pid = fork();
	if (!info->pid)
	{
		// printf("file to pipe =======> %d\n", info->pid);
		first_cmd(info->av, cmd, info);
		// waitpid(info->pid, NULL, 0);
		exit(0);

	}
	
	close(info->pfd[0]);
	close(info->pfd[1]);
}

void	pipe_to_pipe(t_data *info, t_cmd *cmd)
{
	pipe(info->pfd);
	info->pid = fork();
	if (!info->pid)
	{
		// printf("pipe to pipe =======> %d\n", info->pid);
		mid_cmd(cmd, info);
		// waitpid(info->pid, NULL, 0);
		// exit(0);
	}
	// waitpid(info->pid, NULL, 0);
	
	
	close(info->pfd[0]);
	close(info->pfd[1]);
}

void	pipe_to_file(t_data *info, t_cmd *cmd)
{
	// info->fd[1] = open(info->av[info->ac - 1], O_TRUNC | O_RDWR | O_CREAT , 0666);
	info->fd[1] = open(info->av[info->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (info->fd[1] == -1)
	{
		perror("Open Failed\n");
		return ;
	}
	pipe(info->pfd);
	info->pid = fork();
	if (!info->pid)
	{
		// printf("pipe to file =======> %d\n", info->pid);
		last_cmd(cmd, info);
		// waitpid(info->pid, NULL, 0);
	}

	// char *buffer;
	// buffer = (char *) malloc (1000);
	// buffer [999] = 0;
	// // fprintf(stderr, "access fd == %d\n", open(info->av[info->ac - 1], W_OK));
	// fprintf(stderr, "parent fd[1] == %d\n", info->fd[1]);
	// fprintf(stderr, "===> %zd\n", read(info->fd[1], buffer, 1));
	// fprintf(stderr,"--> %c\n", buffer[0]);
	// free (buffer);
	
	close(info->pfd[0]);
	close (info->pfd[1]);
	close (info->fd[1]);
}

void	executions(t_cmd **list, t_data *info)
{
	t_cmd *head;
	t_cmd *tail;
	t_cmd *iter;

	head = *list;
	tail = last_node(*list);
	iter = *list;
	while (iter)
	{
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
