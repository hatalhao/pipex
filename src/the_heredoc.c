/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:32:29 by hatalhao          #+#    #+#             */
/*   Updated: 2024/08/04 06:15:56 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_cmd	**init_list_heredoc(t_cmd **list, t_data *info)
{
	int		i;
	t_cmd	*new_node;

	i = 3;
	list = (t_cmd **)malloc(sizeof(t_cmd *));
	if (!list)
		return (NULL);
	*list = 0;
	while (i < info->ac - 1)
	{
		new_node = make_node(info, info->av[i++]);
		if (!new_node)
			free_list(list);
		add_to_list(list, new_node);
	}
	return (list);
}

/*		*/
t_data	*heredoc_assignements(t_data *info, int ac, char **av, char **envp)
{
	info = (t_data *)malloc(sizeof(t_data));
	if (!info)
		return (NULL);
	info->infile = open("/tmp/.heredoc_", O_RDWR | O_CREAT | O_APPEND, 0666);
	info->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (info->infile == -1 || info->outfile == -1)
		return (free(info), NULL);
	info->paths = get_paths(envp_path(envp));
	info->non_cmd = 4;
	info->envp = envp;
	info->limiter = ft_join(ft_duplicate(av[2]), ft_duplicate("\n"));
	info->ac = ac;
	info->av = av;
	return (info);
}

/*		Fill the heredoc	*/
void	fill_the_doc(t_data *info)
{
	char	*input;
	size_t	input_len;
	size_t	limiter_len;

	limiter_len = ft_length(info->limiter);
	while (1)
	{
		input = get_next_line(0, 0);
		input_len = ft_length(input);
		if (!ft_strncmp(input, info->limiter, input_len)
			&& input_len == limiter_len)
			return (free(input), (void)get_next_line(0, 1));
		ft_putstr_fd(input, info->infile);
		free(input);
	}
}

/*		This function is to reposition the write/read
offset since lseek() is not allowed		*/
void	offset_reposition(t_data *info)
{
	close(info->infile);
	info->infile = open("/tmp/.heredoc_", O_RDWR, 0666);
	if (info->infile == -1)
		exit(1);
}
// will need cleaning up if (info->infile == -1)

/*		Outline how the heredoc scenario will work		*/
void	pipex_heredoc(int ac, char **av, char **envp)
{
	t_cmd	**list;
	t_data	*info;

	info = 0;
	info = heredoc_assignements(info, ac, av, envp);
	if (!info)
		exit(1);
	list = 0;
	list = init_list_heredoc(list, info);
	if (!list)
		exit(1);
	fill_the_doc(info);
	offset_reposition(info);
	executions(list, info);
	ft_putstr_fd("HERE\n", 2);
	final_curtain(list, info, 1);
}
