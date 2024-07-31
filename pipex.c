/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:05:18 by hatalhao          #+#    #+#             */
/*   Updated: 2024/07/31 18:24:24 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

void	final_curtain(t_cmd **list, t_data *info)
{
	close(info->pipefd[0]);
	close(info->pipefd[1]);
	free_list (list);
	free_arr (info->paths);
	free (info);
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
	info = (t_data*) malloc (sizeof(t_data));
	if (!info)
		return (NULL);
	if (!ft_strncmp(av[1], "here_doc", 8) && ft_length(av[1]) == 8)
	{
		info->infile = open("/nfs/homes/hatalhao/Desktop/pipex/here_doc", O_CREAT | O_RDWR | O_APPEND, 0666);
		unlink("/nfs/homes/hatalhao/Desktop/pipex/here_doc");
		if (info->infile == -1)
			ft_printf("HERE -1\n");
		info->limiter = av[2];
	}
	else
		info->infile = open(av[1], O_RDWR);
	// sleep (100);
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
	t_cmd	*new_node;
	t_data	*info;
	int		i;

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
		new_node = make_node(info, info->av[i++]);
		if (!new_node)
			free_list(list);
		add_to_list(list, new_node);
	}
	executions(list, info);
	final_curtain(list, info);
}

int	main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return (1);
		
	pipex(ac, av, envp);
	return (0);
}
