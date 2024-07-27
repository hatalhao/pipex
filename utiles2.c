/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 06:34:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/07/27 00:39:59 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*last_node(t_cmd *list)
{
	if (!list)
		return (NULL);
	while (list)
	{
		if (!list->next)
			return (list);
		list = list->next;
	}
	return (list);
}

void	first_cmd(t_cmd *cmd, t_data *info)
{
	if (dup2 (info->fd[0], 0) == -1 || dup2(info->pipefd[1], 1) == -1)
		return (perror("DUP2 FAILED\n"));
	close (info->fd[0]);
	close(info->pipefd[0]);
	close(info->pipefd[1]);
	fprintf(stderr, "--> HERE\n");
	execve (cmd->path, cmd->args, NULL);
}


void	mid_cmd(t_cmd *cmd, t_data *info)
{
	fprintf(stdout,"--> HERE <--\n");
	// char *buffer;
	// buffer = (char *) malloc (1000);
	// buffer [999] = 0;
	// fprintf(stderr, "===> %zd\n", read(0, buffer, 200));
	// fprintf(stderr,"--> %s\n", buffer);
	fprintf(stderr, "----------------- II ---------------\n");

	close(info->pipefd[0]);
	if (dup2(info->pipefd[1], 1) == -1)
		return (perror("DUP2 FAILED\n"));

	close(info->pipefd[1]);
	if (execve(cmd->path, cmd->args, NULL) == -1)
	{
		perror("EXECVE FAILED\n");
		exit (1);
	}
}

void	last_cmd(t_cmd *cmd, t_data *info)
{
	fprintf(stderr, "----------------- I2 ---------------\n");
	close(info->pipefd[1]);
	// if (dup2 (info->pipefd[0], 0) == -1)
	// 	return (perror("DUP2 FAILED\n"));
	close (info->pipefd[0]);
	if (dup2 (info->fd[1], 1) == -1)
		return (perror("DUP2 FAILED\n"));
	close (info->fd[1]);
	execve(cmd->path, cmd->args, NULL);
}

t_cmd	*make_node(t_data *info, char *av)
{
	t_cmd *new;

	new = (t_cmd *) malloc (sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = get_args (av);
	new->path = extract_path(info->paths, new);
	new->next = NULL;
	return (new);
}
