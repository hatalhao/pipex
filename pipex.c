/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:05:18 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/13 00:31:49 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"



// int	cmd_access(t_data *info, t_cmd *cmd)
// {
// 	int	v;

// 	v = 0;
// 	v = access(cmd->path, X_OK);
// 	if (v == 0)
// 		return ();
// }


void	add_to_list(t_cmd **list, t_cmd *new)
{
	if (!list || !*list)
		*list = new;
	else
		(last_node(*list))->next = new;
}

// void	preliminaries(int ac, char **av, char **envp)
// {
// 	int pfd[2];
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
// 		pipe(pfd);
// 		if (!(pid[t] = fork()))
// 		{
// 			fd[0] = open(*av, O_RDONLY);
// 			close(pfd[0]);
// 			dup2(fd[0], 0);
// 			dup2(pfd[1], 1);
// 			execve(cmd1->path, cmd1->args, NULL);
// 		}
// 		waitpid(pid[t++], NULL, 0);
// 		if (!(pid[t] = fork()))
// 		{
// 			fd[1] = open(*(av + 3), O_RDWR | O_CREAT, 0666);
// 			close(pfd[1]);
// 			dup2(pfd[0], 0);
// 			dup2(fd[1], 1);
// 			execve(cmd2->path, cmd2->args, NULL);
// 		}
// 		close (pfd[1]);
// 		waitpid(-1, NULL, 0);
// 		close (pfd[0]);
// 		free_arr(paths);
// 		free_struct(cmd1);
// 		free_struct(cmd2);
// 		free(pid);
// 		free(fd);
// 	}
// }

t_data	*assignements(t_data *info, int ac, char **av, char **envp)
{
	info = (t_data*) malloc (sizeof(t_data));
	if (!info)
		return (NULL);
	info->fd = (int *) malloc (sizeof(int) * 2);
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
	list = (t_cmd **) malloc (sizeof(t_cmd));
	if (!list)
		exit(1);
	*list = 0;
	info = assignements(info, ac, av, envp);
	i = 2;
	while (i < ac - 1)
		add_to_list(list, mk_node(info, info->av[i++]));
	executions(list, info);
	wait(NULL);
	close(info->pfd[0]);
	close(info->pfd[1]);
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
	printf("dd\n");
	return (0);
}
