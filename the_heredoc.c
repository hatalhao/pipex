#include "pipex.h"

t_data	*assignements(t_data *info, int ac, char **av, char **envp)
{

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

