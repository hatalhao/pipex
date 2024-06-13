/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 06:34:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/13 02:02:28 by hatalhao         ###   ########.fr       */
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
	fprintf(stderr, "****HERE\n");
	info->fd[0] = open(*av, O_RDONLY);
	dup2 (info->fd[0], 0);
	close (info->fd[0]);
	dup2 (info->pfd[1], 1);
	
	// char *buffer;
	// buffer = (char *) malloc (1000);
	// buffer [999] = 0;
	// fprintf(stderr, "===> %zd\n", read(0, buffer, 100));
	// fprintf(stderr,"--> %s\n", buffer);
	
	close(info->pfd[0]);
	execve (cmd->path, cmd->args, NULL);
}





void	mid_cmd(t_cmd *cmd, t_data *info)
{
	dup2(info->pfd[0], 0);
	close(info->pfd[0]);
	// dup2(info->pfd[1], 1);
	close(info->pfd[1]);
	execve(cmd->path, cmd->args, NULL);
}




void	last_cmd(t_cmd *cmd, t_data *info)
{
	close(info->pfd[1]);
	dup2(info->pfd[0], 0);
	dup2(info->fd[1], 1);
	close(info->pfd[0]);
	// close (info->fd[1]);
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
