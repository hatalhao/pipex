#include "pipex.h"

void    ft_exp()
{
	int	pfd[2];
	int pid[3];
	int fd[3];
	char **av;

	av = NULL;
	fd[0] = open ("pipex.h", O_RDONLY);
	fd[1] = open("output", O_RDWR | O_CREAT, 0666);
	pipe(pfd);
	pid[0] = fork();
	if (!pid[0])
	{
		close (pfd[0]);
		dup2(fd[0], 0);
		dup2(pfd[1], 1);
		execve("/usr/bin/cat", av, NULL);
	}
	waitpid(pid[0], NULL, 0);
	pid[1] = fork();
	if (!(pid[1]))
	{
		close (pfd[1]);
		dup2(pfd[0], 0);
		dup2(fd[1], 1);
		execve("/usr/bin/wc", av, NULL);
	}
}

int main()
{
	ft_exp();
	return (0);
}