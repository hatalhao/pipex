/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:05:18 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/01 06:18:54 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	final_curtain(t_cmd **list, t_data *info)
{
	close(info->pipefd[0]);
	close(info->pipefd[1]);
	free_list (list);
	free_arr (info->paths);
	free (info);
}

/**/
t_cmd	**fill_list(t_cmd **list, t_data *info)
{
	int		i;
	t_cmd	*new_node;

	list = (t_cmd **) malloc (sizeof(t_cmd *));
	if (!list)
		return (NULL);
	i = 2;
	while (i < info->ac - 1)
	{
		new_node = make_node(info, info->av[i++]);
		if (!new_node)
			free_list(list);
		add_to_list(list, new_node);
	}
	return (list);
}

/*		This function adds a node to a linked list		*/
void	add_to_list(t_cmd **list, t_cmd *new)
{
	if (!list || !*list)
		*list = new;
	else
		(last_node(*list))->next = new;
}

/*		This function allocates memory for the struct info (check the header file) and assigns values to the struct's variables */
t_data	*assignements(t_data *info, int ac, char **av, char **envp)
{
	info = (t_data *) malloc (sizeof(t_data));
	if (!info)
		return (NULL);
	info->infile = open(av[1], O_RDWR);
	info->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC);
	if (info->infile == -1 || info->outfile == -1)
		return (NULL);
	info->paths = get_paths(envp_path(envp));
	info->ac = ac;
	info->av = av;
	info->envp = envp;
	return (info);
}

void	pipex(int ac, char **av, char **envp)
{
	t_cmd	**list;
	t_data	*info;

	info = NULL;
	info = assignements(info, ac, av, envp);
	if (!info)
		exit (1);
	list = 0;
	list = fill_list(list, info);
	executions(list, info);
	final_curtain(list, info);
}
