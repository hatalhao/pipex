/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:05:18 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/05 23:15:20 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

char **get_args(char *cmd)
{
	char **args;

	args = NULL;
	args = ft_split(cmd, ' ');
	return (args);
}

void free_arr(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

char **get_paths(char *envp)
{
	char **paths;

	if (!envp)
		return (NULL);
	paths = ft_split(envp, ':');
	return (paths);
}

char *extract_path(char **paths, t_cmd *cmd)
{
	char *buffer;
	int v;
	int i;

	i = 0;
	buffer = NULL;
	while (paths[i])
	{
		buffer = ft_join(ft_join(ft_duplicate(paths[i]), ft_duplicate("/")), ft_duplicate(*(cmd->args)));
		v = access(buffer, X_OK);
		if (!v)
		{
			printf("ACCESS GRANTED\n");
			break;
		}
		free(buffer);
		i++;
	}
	if (v == -1)
	{
		buffer = NULL;
		printf("ACCESS_FAILURE\n");
	}
	return (buffer);
}



// void	assignements()
// {
	
// }

char	*envp_path(char **envp)
{
	int		i;
	char	*path;
	
	i = 0;
	path = NULL;
	while (envp && envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
		{
			path = envp[i];
			return (path);
		}
		i++;
	}
	return (path);
}

void	free_struct(t_cmd *cmd)
{
	free_arr(cmd->args);
	free(cmd->path);
	free(cmd);
}

void	last_cmd(char **av, t_cmd *cmd, int *fd, int *pfd)
{
	fd[1] = open(*(av + 3), O_RDWR | O_CREAT, 0666);
	close(pfd[1]);
	dup2(pfd[0], 0);
	dup2(fd[1], 1);
	execve(cmd->path, cmd->args, NULL);
}

void	mid_cmd(t_cmd *cmd)
{
	close(pfd);
	dup2();
	dup2();
	execve();
}
void	first_cmd(char **av, t_cmd *cmd, int *fd, int *pfd)
{
	fd[0] = open(*av, O_RDONLY);
	dup2 (fd[0], 0);
	dup2 (pfd[1], 1);
	execve (cmd->path, cmd->args, NULL);	
}

void preliminaries(int ac, char **av, char **envp)
{
	int pfd[2];
	char **paths;

	t_cmd *cmd1;
	t_cmd *cmd2;
	int i;
	int j;
	int *pid;
	int *fd;

	int n = ac - 3;
	int t = 0;
	pid = (int *)malloc(sizeof(int) * n);
	fd = (int *)malloc(sizeof(int) * 2);
	cmd1 = (t_cmd *)malloc(sizeof(t_cmd));
	cmd2 = (t_cmd *)malloc(sizeof(t_cmd));
	i = 0;
	j = 1;
	if (access(*av, X_OK) == 0)
		cmd1->path = *av;
	else
	{
		paths = get_paths((envp_path(envp)));
		cmd1->args = get_args(*(av + 1));
		cmd2->args = get_args(*(av + 2));
		cmd1->path = extract_path(paths, cmd1);
		cmd2->path = extract_path(paths, cmd2);
		if (!(cmd1->path) || !(cmd2->path))
		{
			perror("Path not found\n");
			free_arr(paths);
			free_struct(cmd1);
			free_struct(cmd2);
			free(pid);
			free(fd);
			exit(1);
		}
		pipe(pfd);
		if (!(pid[t] = fork()))
		{
			fd[0] = open(*av, O_RDONLY);
			close(pfd[0]);
			dup2(fd[0], 0);
			dup2(pfd[1], 1);
			execve(cmd1->path, cmd1->args, NULL);
		}
		waitpid(pid[t++], NULL, 0);
		if (!(pid[t] = fork()))
		{
			fd[1] = open(*(av + 3), O_RDWR | O_CREAT, 0666);
			close(pfd[1]);
			dup2(pfd[0], 0);
			dup2(fd[1], 1);
			execve(cmd2->path, cmd2->args, NULL);
		}
		close (pfd[1]);
		waitpid(-1, NULL, 0);
		close (pfd[0]);
		free_arr(paths);
		free_struct(cmd1);
		free_struct(cmd2);
		free(pid);
		free(fd);
	}
}

int main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return (1);
	preliminaries(ac, av + 1, envp);
	// parsing_();
	return (0);
}
