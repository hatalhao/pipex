#include "pipex.h"

/**/
t_data	*heredoc_assignements(t_data *info, int ac, char **av, char **envp)
{
	info = (t_data *) malloc (sizeof(t_data));
	if (!info)
		return (NULL);
	info->infile = open(av[1], O_RDWR | O_CREAT, 0666);
	info->outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND);
	if (info->infile == -1 || info->outfile == -1)
		return (NULL);
	info->limiter = av[2];
	info->paths = get_paths(envp_path(envp));
	info->ac = ac;
	info->av = av;
	info->envp = envp;
	return (info);
}

/**/
void	fill_the_doc(t_data *info)
{
	char	*input;
	size_t	input_len;
	size_t	limiter_len;

	limiter_len = ft_length(info->limiter);
	while (1)
	{
		input = get_next_line(0);
		input_len = ft_length(input);
		if (!ft_strncmp(input, info->limiter, input_len)
			&& input_len == limiter_len)
		{
			free(input);
			return ;
		}
		ft_putstr_fd(input, info->infile);
		free (input);
	}
}

void	heredoc_init(t_data *info, t_cmd ***list, int ac, char **av, char **envp)
{
	info = NULL;
	info = heredoc_assignements(info, ac, av, envp);
	if (!info)
		exit(1);
	*list = (t_cmd **) malloc (sizeof(t_cmd *));
	if (!list)
		exit(1);
	*list = 0;
}

/**/
void	pipex_heredoc(int ac, char **av, char **envp)
{
	t_cmd	**list;
	t_data	*info;

	info = 0;
	heredoc_init(info, &list, ac, av, envp);

}
