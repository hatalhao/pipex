/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_and_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:23:36 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/04 04:24:36 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*cmd_absolute_path(char *full_path)
{
	if (access(full_path, X_OK) == -1)
		return (NULL);
	return (ft_duplicate(full_path));
}

char	**get_args(char *cmd)
{
	char	**args;

	args = NULL;
	args = ft_split(cmd, ' ');
	return (args);
}

char	**get_paths(char *envp)
{
	char	**paths;

	if (!envp)
		return (NULL);
	paths = ft_split(envp + 5, ':');
	return (paths);
}

char	*extract_path(char **paths, t_cmd *cmd)
{
	char	*buffer;
	int		v;
	int		i;

	i = 0;
	buffer = NULL;
	buffer = cmd_absolute_path(cmd->args[0]);
	if (buffer)
		return (buffer);
	while (paths[i])
	{
		buffer = ft_join(ft_join(ft_duplicate(paths[i++]), ft_duplicate("/")),
				ft_duplicate(*(cmd->args)));
		v = access(buffer, X_OK);
		if (!v)
			return (buffer);
		ft_free(&buffer);
	}
	if (v == -1)
		buffer = NULL;
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
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			path = envp[i];
			return (path);
		}
		i++;
	}
	return (path);
}
