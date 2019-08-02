#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main ()
{
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if(pid == 0)
	{
		close(fd[0]);
		int ret = dup2(fd[1],STDOUT_FILENO);
		if(ret == 1)
		{
			execlp("ps","ps","aux",NULL);
		}
		else
		{
			return -1;
		}
	}

	if(pid > 0)
	{
		close(fd[1]);
		int ret2 = dup2(fd[0],STDIN_FILENO);
		if(ret2 == 0)
		{
			execlp("grep","grep","bash",NULL);
		}
		else
		{
			return -2;
		}
	}
	return 0;
}
