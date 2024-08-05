/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:15:31 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 15:11:47 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*		Clean all open file descriptors heap-allocated memory		*/
void	final_curtain(t_cmd **list, t_data *info, int flag)
{
	if (list)
		free_list(list);
	free_arr(info->paths);
	if (flag == 1)
	{
		free(info->limiter);
		if (unlink("/tmp/.heredoc_") == -1)
			error_exit();
	}
	free(info);
}

/*		Initialise a linked list		*/
t_cmd	**init_list(t_cmd **list, t_data *info)
{
	int		i;
	t_cmd	*new_node;

	i = 2;
	list = (t_cmd **)malloc(sizeof(t_cmd *));
	if (!list)
		return (NULL);
	*list = 0;
	while (i < info->ac - 1)
	{
		new_node = make_node(info, info->av[i++]);
		if (!new_node)
		{
			free_list(list);
			return (NULL);
		}
		add_to_list(list, new_node);
	}
	return (list);
}

/*		Add a node to a linked list.	*/
void	add_to_list(t_cmd **list, t_cmd *new_node)
{
	if (!*list)
		*list = new_node;
	else
		(last_node(*list))->next = new_node;
}

/*		Allocate memory for the struct s_data (check the header file)
and assign values to the struct's variables.	*/
t_data	*assignements(t_data *info, int ac, char **av, char **envp)
{
	info = (t_data *)malloc(sizeof(t_data));
	if (!info)
		return (NULL);
	info->infile = open(av[1], O_RDWR);
	info->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	info->paths = get_paths(envp_path(envp));
	if (info->infile == -1)
		return (clean_data_mandatory(info, 1), exit(1), NULL);
	else if (info->outfile == -1)
		return (clean_data_mandatory(info, 0), exit(1), NULL);
	else if (!info->paths)
		return (clean_data_mandatory(info, 2), exit(1), NULL);
	info->non_cmd = 3;
	info->envp = envp;
	info->limiter = 0;
	info->ac = ac;
	info->av = av;
	return (info);
}

void	pipex(int ac, char **av, char **envp)
{
	t_cmd	**list;
	t_data	*info;

	info = NULL;
	list = 0;
	info = assignements(info, ac, av, envp);
	if (!info)
		exit(1);
	list = init_list(list, info);
	if (!list)
		return (final_curtain(list, info, 0));
	executions(list, info);
	final_curtain(list, info, 0);
}
