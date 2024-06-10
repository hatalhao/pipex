/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 06:34:06 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/10 07:11:08 by hatalhao         ###   ########.fr       */
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

void	last_cmd(char **av, t_cmd *cmd, int *fd, int *pfd)
{
	fd[1] = open(*(av + 3), O_RDWR | O_CREAT, 0666);
	close(pfd[1]);
	dup2(pfd[0], 0);
	dup2(fd[1], 1);
	execve(cmd->path, cmd->args, NULL);
}

void	mid_cmd(t_cmd *cmd, int *pfd)
{
	dup2(pfd[0], 0);
	dup2(pfd[1], 1);
	execve(cmd->path, cmd->args, NULL);
}
void	first_cmd(char **av, t_cmd *cmd, int *fd, int *pfd)
{
	fd[0] = open(*av, O_RDONLY);
	close(pfd[0]);
	dup2 (fd[0], 0);
	dup2 (pfd[1], 1);
	execve (cmd->path, cmd->args, NULL);	
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
