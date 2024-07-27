#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "pipex.h"
#include <sys/stat.h>

void	pipexx(int fd)
{
	int *pipefd1;
	int *pipefd2;
	int pid;

	if (pipe(pipefd1) == -1)
		return (perror("pipe failed\n"));
	pid = fork();
	if (pid == -1)
		return (perror("fork failed\n"));
	if (pid == 0)
	{
		if (dup2(fd, 0) == -1 || dup2(pipefd1[1], 1) == -1)
			return (perror("dup2 failed\n"));
	}
	else
	{

	}
}

int main()
{
	int keeper = open("/home/hamza/pipex/Makefile", O_RDWR , 0666);
	// int keeper = open("/home/hamza/pipex", __O_TMPFILE | O_RDWR  , 0666);
	char *s = "Hello World 11\n";
	size_t	len = ft_length(s);
	// struct stat *buffer;
	// buffer = 0;
	if (write (keeper, s, len))
	{
		// fstat(keeper, buffer);
		// printf("st_ino == %lu\n", buffer->st_ino);
		// sleep (3);
		char *buf = (char *) calloc (len + 1, sizeof(char));
		buf[len] = 0;
		// int keeper_2 = open("/home/hamza/pipex/temp", O_CREAT | O_RDWR  , 0666);
		int keeper_2 = open("/home/hamza/pipex", __O_TMPFILE | O_RDWR  , 0666);
		read(keeper_2, buf, len);
		printf("buf == %s\n", buf);
		free (buf);
		sleep (100);
		close (keeper);
		close (keeper_2);
	}
	return (0);
}