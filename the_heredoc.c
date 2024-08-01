#include "pipex.h"

t_data	*heredoc_assignements(t_data *info, int ac, char **av, char **envp)
{
	info = (t_data*) malloc (sizeof(t_data));
	if (!info)
		return (NULL);
	info->infile = open(av[1], O_RDWR);
	info->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND);
	info->paths = get_paths(envp_path(envp));
	info->ac = ac;
	info->av = av;
	info->envp = envp;
	return (info);
}

void	fill_the_doc(t_cmd **list, t_data *info)
{
	char	*input;
	while (1)
	{
		input = get_next_line(0);
		if (!strncmp(input, info->limiter, ft_length(input)) && ft_length(input) == ft_length(info->limiter))
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, info->infile);
		free (input);
	}
}

void	pipex_heredoc(ac, av, envp)
{
	t_cmd	**list;
	t_cmd	*new_node;
	t_data	*info;

	info = NULL;
	info = heredoc_assignements(info, ac, av, envp);
	if ()
	list = (t_cmd **) malloc (sizeof(t_cmd *));
	if (!list)
		exit(1);
	*list = 0;

}
