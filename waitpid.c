#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
int main ()
{
	pid_t pid = fork();
	if (pid == 0)
	{
		printf ("i am child pid = %d\n",getpid());
		sleep(2);
	}
	else if (pid > 0)
	{
		printf ("i am father pid=%d\n",getpid());
		int ret = waitpid(-1,NULL,WNOHANG);
		printf ("%d\n",ret);
		while (1)
		{
			sleep(1);
		}
	}
	return 0;
}
