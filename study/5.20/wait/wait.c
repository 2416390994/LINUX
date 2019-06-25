#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main ()
{
	int pid = fork();
	if (pid < 0)
	{
		perror("error");
		exit(-1);
	}else if (pid == 0)
	{
		sleep (5);
		exit(0);
	}
	while (1)
	{
		printf("i am partent!\n");
		sleep(1);
	}
	return 0;
}

