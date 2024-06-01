/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:05:18 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/01 20:24:16 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

char	**get_args(char *cmd)
{
	char	**args;

	args = NULL;
	args = ft_split(cmd, ' ');
	return (args);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free (arr[i++]);
	free (arr);
}

char	**get_paths(char *envp)
{
	char	**paths;

	if (!envp)
		return (NULL);
	paths = ft_split(envp, ':');
	return (paths);
}

void	preliminaries(int ac, char **av, char **envp)
{
	int		pfd[2];
	char	**paths;
	char	*buffer;
	t_cmd	*cmd1;
	t_cmd	*cmd2;
	int		v;
	int		i;
	int		j;
	int		*pid;
	int		*fd;

	int n = ac - 3;
	int t = 0;
	pid = (int *) malloc (sizeof(int) * n);
	fd = (int *) malloc (sizeof(int) * 2);
	for (int i = 0; i < n; i++)
		
	fd[0] = open(*av, O_RDONLY);
	fd[1] = open (*(av + 3), O_CREAT, O_RDWR);
	cmd1 = (t_cmd *) malloc (sizeof(t_cmd));
	cmd2 = (t_cmd *) malloc (sizeof(t_cmd));
	i = 0;
	j = 1;
	if (access(*av, X_OK) == 0)
		buffer = *av;
	else
	{
		while (envp && envp[i])
		{
			if (!ft_strncmp("PATH", envp[i], 4))
				break ;
			i++;
		}
		paths = get_paths((envp[i]));
		while (paths[j])
			printf("==> %s\n", paths[j++]);
		i = 1;
		cmd1->args = get_args(*(av + 1));
		cmd2->args = get_args(*(av + 3));
		while (paths[i] && (t < n))
		{
			buffer = ft_join(ft_join(ft_duplicate(paths[i]), ft_duplicate("/")), ft_duplicate(*(cmd1->args)));
			printf("buffer -------> %s\n", buffer);
			v = access(buffer, X_OK);
			if (v == 0)
			{
				printf("ACCESS GRANTED\n");
				cmd1->path = buffer;
				pipe(pfd);
				if (!(pid[t] = fork()))
				{
					dup2(fd[0], 0);
					dup2(pfd[1], 1);
					// sleep(2);
					execve(buffer, cmd1->args, NULL);
				}
				waitpid(pid[t], NULL, 0);
				t++;
				// char *buf;
				// buf = (char *) malloc (11);
				// buf[10] = '\0';
				// printf("BUF == ---------------------->>> %s\n", buf);
				// read (pfd[1], buf, 5);
				// buf[10] = '\0';
				// printf("BUF == ---------------------->>> %s\n", buf);
				if (!(pid[t] = fork()))
				{
					dup2(pfd[0], 0);
					dup2(fd[1], 1);
					
				}
				// waitpid(pid[t], NULL, 0);
				free (buffer);
				free_arr(paths);
				free_arr (cmd1->args);
				free (cmd1);
				free_arr (cmd2->args);
				free (cmd2);
				free (pid);
				free (fd);
				break ;
			}
			printf("v = %d, Therefore, %s is Not in This Path\n", v, *(av + 1));
			printf("----------------------------------------------------------------\n");
			free (buffer);

			i++;
		}
		if (v == -1)
		{
			printf("ACCESS_FAILURE");
			free_arr(paths);
			exit (1);
		}
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
