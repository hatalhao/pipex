/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 02:05:18 by hatalhao          #+#    #+#             */
/*   Updated: 2024/05/12 21:30:56 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	**paths;
	char	*buffer;
	t_cmd	*cmd;
	int		v;
	int		i;
	int		j;

	cmd = (t_cmd *) malloc (sizeof(t_cmd));
	i = 0;
	j = 1;
	if (!access(*av, X_OK))
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
		while (paths[i] && v != 0)
		{
			buffer = ft_join(ft_join(ft_duplicate(paths[i]), ft_duplicate("/")), ft_duplicate(*av));
			printf("buffer -------> %s\n", buffer);
			v = access(buffer, X_OK);
			if (v == 0)
			{
				printf("ACCESS GRANTED\n");
				cmd->args = get_args(*av);
				cmd->path = buffer;
				execve(buffer, av, NULL);
				printf("Here\n");
				free (buffer);
				free_arr(paths);
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
			exit (1);
		}
	}
}

int main(int ac, char **av, char **envp)
{
	if (ac == 5)
		return (1);
	preliminaries(av + 1, envp);
	// parsing();
	return (0);
}
