#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
int main()
{
	pid_t pid;
	pid =fork();
	if(pid == 0)
	{
		exit(EXIT_SUCCESS);
	}
	int status;
	int ret = wait(&status);
	printf ("%d",(status>>8)&0xff);
	return 0;
}
