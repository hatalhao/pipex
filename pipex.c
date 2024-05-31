/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:05:18 by hatalhao          #+#    #+#             */
/*   Updated: 2024/05/31 20:57:08 by hatalhao         ###   ########.fr       */
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

void	preliminaries(char **av, char **envp)
{
	int		pfd[2];
	char	**paths;
	char	*buffer;
	t_cmd	*cmd;
	int		v;
	int		i;
	int		j;
	int		pid;
	int		fd;
	int		fd2;

	fd = open(*av, O_RDONLY);
	fd2 = open (*(av + 3), O_CREAT, O_RDWR);
	printf("fd2 == %i\n", fd2);
	cmd = (t_cmd *) malloc (sizeof(t_cmd));
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
		cmd->args = get_args(*(av + 1));
		while (paths[i])
		{
			buffer = ft_join(ft_join(ft_duplicate(paths[i]), ft_duplicate("/")), ft_duplicate(*(cmd->args)));
			printf("buffer -------> %s\n", buffer);
			v = access(buffer, X_OK);
			if (v == 0)
			{
				printf("ACCESS GRANTED\n");
				cmd->path = buffer;
				pipe(pfd);
				pid = fork();
				if (pid == 0)
				{
					close(pfd[1]);
					dup2(fd, 0);
					sleep(2);
					execve(buffer, cmd->args, NULL);
					printf("===> This is Child\n");
				}
				waitpid(pid, NULL, 0);
				dup2(1, fd2);
				free (buffer);
				free_arr(paths);
				free_arr (cmd->args);
				free (cmd);
				break ;
			}
			printf("v = %d, Therefore, ls is Not in This Path\n", v);
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
	if (ac == 5)
		return (1);
	preliminaries(av + 1, envp);
	// parsing_();
	return (0);
}
