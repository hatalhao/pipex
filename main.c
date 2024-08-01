#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return (1);
	heredoc_or_simple_file(ac, av, envp);
	return (0);
}
