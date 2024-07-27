/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:05:18 by hatalhao          #+#    #+#             */
/*   Updated: 2024/07/27 06:44:57 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



// int	cmd_access(t_data *info, t_cmd *cmd)
// {
// 	int	v;

// 	v = 0;
// 	v = access(cmd->path, X_OK);
// 	if (v == 0)
// 		return ();
// }



// void	preliminaries(int ac, char **av, char **envp)
// {
// 	int pipefd[2];
// 	char **paths;
// 	t_cmd *cmd1;
// 	t_cmd *cmd2;
// 	int i;
// 	int j;
// 	int *pid;
// 	int *fd;

// 	int n = ac - 3;
// 	int t = 0;
// 	pid = (int *)malloc(sizeof(int) * n);
// 	fd = (int *)malloc(sizeof(int) * 2);
// 	cmd1 = (t_cmd *)malloc(sizeof(t_cmd));
// 	cmd2 = (t_cmd *)malloc(sizeof(t_cmd));
// 	i = 0;
// 	j = 1;
// 	if (access(*av, X_OK) == 0)
// 		cmd1->path = *av;
// 	else
// 	{
// 		paths = get_paths((envp_path(envp)));
// 		cmd1->args = get_args(*(av + 1));
// 		cmd2->args = get_args(*(av + 2));
// 		cmd1->path = extract_path(paths, cmd1);
// 		cmd2->path = extract_path(paths, cmd2);
// 		if (!(cmd1->path) || !(cmd2->path))
// 		{
// 			perror("Path not found\n");
// 			free_arr(paths);
// 			free_struct(cmd1);
// 			free_struct(cmd2);
// 			free(pid);
// 			free(fd);
// 			exit(1);
// 		}
// 		pipe(pipefd);
// 		if (!(pid[t] = fork()))
// 		{
// 			fd[0] = open(*av, O_RDONLY);
// 			close(pipefd[0]);
// 			dup2(fd[0], 0);
// 			dup2(pipefd[1], 1);
// 			execve(cmd1->path, cmd1->args, NULL);
// 		}
// 		waitpid(pid[t++], NULL, 0);
// 		if (!(pid[t] = fork()))
// 		{
// 			fd[1] = open(*(av + 3), O_RDWR | O_CREAT, 0666);
// 			close(pipefd[1]);
// 			dup2(pipefd[0], 0);
// 			dup2(fd[1], 1);
// 			execve(cmd2->path, cmd2->args, NULL);
// 		}
// 		close (pipefd[1]);
// 		waitpid(-1, NULL, 0);
// 		close (pipefd[0]);
// 		free_arr(paths);
// 		free_struct(cmd1);
// 		free_struct(cmd2);
// 		free(pid);
// 		free(fd);
// 	}
// }

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
	info->fd = (int *) malloc (sizeof(int) * 2);
	if (!info->fd)
		return (NULL);
	info->fd[0] = open(av[1], O_RDONLY);
	info->fd[1] = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (info->fd[0] == -1 || info->fd[1] == -1)
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
		add_to_list(list, make_node(info, info->av[i++]));
	executions(list, info);
	close(info->pipefd[0]);
	close(info->pipefd[1]);
	free_list (list);
	free_arr (info->paths);
	free (info->fd);
	free (info);
}

int	main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return (1);
	// preliminaries(ac, av + 1, envp);
	pipex(ac, av, envp);
	// sleep (100);
	// fprintf(stderr ,"dd\n");
	return (0);
}
