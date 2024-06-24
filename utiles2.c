/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 06:34:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/24 16:57:08 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

t_cmd	*last_node(t_cmd *list)
{
	if (!list)
		return (NULL);
	while (list)
	{
		if (!list->next)
			break ;
		list = list->next;
	}
	return (list);
}

void	first_cmd(char **av, t_cmd *cmd, t_data *info)
{
	info->fd[0] = open(*(av + 1), O_RDONLY);
	if (info->fd[0] == -1)
	{
		perror("Open Failed\n");
		return ;
	}
	if (dup2 (info->fd[0], 0) == -1)
	{
		perror("DUP2 FAILED\n");
		return ;
	}
	if (dup2(info->pfd[1], 1) == -1)
	{
		perror("DUP2 FAILED\n");
		return ;
	}
	close (info->fd[0]);
	close(info->pfd[0]);
	close(info->pfd[1]);
	fprintf(stderr, "HERE\n");
	// char *buffer;
	// buffer = (char *) malloc (1000);
	// buffer [999] = 0;
	// fprintf(stderr, "--- first command ===> %zd\n", read(0, buffer, 200));
	// fprintf(stderr, "--> %s\n", buffer);
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
	if (dup2(info->pfd[0], 0) == -1)
	{
		perror("DUP2 FAILED\n");
		return ;
	}
	fprintf(stderr, "----------------- II ---------------\n");
	// char *buffer;
	// buffer = (char *) malloc (1000);
	// buffer [999] = 0;
	// fprintf(stderr, "===> %zd\n", read(0, buffer, 200));
	// fprintf(stderr,"--> %s\n", buffer);
	close(info->pfd[0]);
	if (dup2(info->pfd[1], 1) == -1)
	{
		perror("DUP2 FAILED\n");
		return ;
	}
	close(info->pfd[1]);
	if (execve(cmd->path, cmd->args, NULL) == -1)
	{
		perror("EXECVE FAILED\n");
		exit (1);
	}
}

void	last_cmd(t_cmd *cmd, t_data *info)
{
	fprintf(stderr, "----------------- I2 ---------------\n");
	// char *buffer;
	// buffer = (char *) malloc (1000);
	// buffer [999] = 0;
	// fprintf(stderr, "===> %zd\n", read(0, buffer, 1));
	// fprintf(stderr,"--> %s\n", buffer);
	close(info->pfd[1]);
	if (dup2 (info->pfd[0], 0) == -1)
	{
		perror("DUP2 FAILED\n");
		return ;
	}
	close (info->pfd[0]);
	if (dup2 (info->fd[1], 1) == -1)
	{
		perror("DUP2 FAILED\n");
		return ;
	}
	close (info->fd[1]);
	execve(cmd->path, cmd->args, NULL);
}

t_cmd	*mk_node(t_data *info, char *av)
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
