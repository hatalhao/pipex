/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:05:18 by hatalhao          #+#    #+#             */
/*   Updated: 2024/07/30 17:19:04 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

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
	info = (t_data*) malloc (sizeof(t_data));
	if (!info)
		return (NULL);
	info->infile = open(av[1], O_RDONLY);
	info->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
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
	int		i;
	t_data	*info;
	t_cmd	**list;
	t_cmd	*new;

	info = NULL;
	list = (t_cmd **) malloc (sizeof(t_cmd *));
	if (!list)
		exit(1);
	*list = 0;
	info = assignements(info, ac, av, envp);
	if (!info)
	{
		free (list);
		exit (1);
	}
	i = 2;
	while (i < ac - 1)
	{
		new = make_node(info, info->av[i++]);
		if (!new)
			free_list(list);
		add_to_list(list, new);
	}
	executions(list, info);
	close(info->pipefd[0]);
	close(info->pipefd[1]);
	free_list (list);
	free_arr (info->paths);
	free (info);
}

int	main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return (1);
	pipex(ac, av, envp);
	return (0);
}
