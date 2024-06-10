/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 06:56:47 by hatalhao          #+#    #+#             */
/*   Updated: 2024/06/10 06:57:48 by hatalhao         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

char	**get_args(char *cmd)
{
	char **args;

	args = NULL;
	args = ft_split(cmd, ' ');
	return (args);
}

char	**get_paths(char *envp)
{
	char **paths;

	if (!envp)
		return (NULL);
	paths = ft_split(envp, ':');
	return (paths);
}

char	*extract_path(char **paths, t_cmd *cmd)
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
