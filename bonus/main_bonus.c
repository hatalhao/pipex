/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 04:22:03 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/05 17:52:07 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/*		Decide if the infile provided is
a heredoc or a file in the filesystem	*/
void	heredoc_or_simple_file(int ac, char **av, char **envp)
{
	if (!ft_strncmp(av[1], "here_doc", ft_length(av[1]))
		&& ft_length(av[1]) == 8)
		pipex_heredoc(ac, av, envp);
	else
		pipex(ac, av, envp);
}

int	main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return (1);
	heredoc_or_simple_file(ac, av, envp);
	return (0);
}
