#include <stdio.h>
#include <unistd.h>

int main()
{
	int keeper = 3;

	if ((keeper = dup(keeper)) == -1) return (perror("dup failed\n"), -8);
	printf("--> [%d]\n", keeper);
	return (0);
}