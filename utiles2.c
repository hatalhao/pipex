/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 06:34:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/07/30 17:39:37 by hatalhao         ###   ########.fr       */
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
			return (list);
		list = list->next;
	}
	return (list);
}

void	first_cmd(t_cmd *cmd, t_data *info)
{
	close(info->pipefd[0]);
	if (dup2 (info->infile, STDIN) == -1 || dup2(info->pipefd[1], STDOUT) == -1)
		return (perror("DUP2 FAILED in first_cmd\n"));
	close (info->infile);
	close(info->pipefd[1]);
	if (execve(cmd->path, cmd->args, NULL) == -1)
	{
		perror("EXECVE FAILED in first_cmd\n");
		exit (1);
	}
}


void	mid_cmd(t_cmd *cmd, t_data *info)
{
	close(info->pipefd[0]);
	if (dup2(info->keeper, STDIN) == -1 || dup2(info->pipefd[1], STDOUT) == -1)	
		return (perror("DUP2 FAILED in mid_cmd\n"));
	close (info->keeper);
	close(info->pipefd[1]);
	if (execve(cmd->path, cmd->args, NULL) == -1)
	{
		perror("EXECVE FAILED in mid_cmd\n");
		exit (1);
	}
}

void	last_cmd(t_cmd *cmd, t_data *info)
{
	close (info->pipefd[0]);
	close(info->pipefd[1]);
	if (dup2 (info->outfile, STDOUT) == -1)
		return (perror("DUP2 FAILED in last_cmd\n"));
	close (info->outfile);
	if (execve(cmd->path, cmd->args, NULL) == -1)
	{
		perror("EXECVE FAILED in last_cmd\n");
		exit (1);
	}
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
