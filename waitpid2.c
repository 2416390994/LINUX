#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main ()
{
	int i;
	pid_t pid;
	for (i=0 ; i< 3 ;i++)
	{
		pid = fork();
		if (pid == 0)
		{
			break;
		}
	}
	if (i < 3)
	{
		sleep(2);
		printf ("i am child i=%d,pid =%d \n",i,getpid());
	}
	else if (i == 3)
	{
		printf ("i am father\n");
		while (1)
		{
			pid_t wpid = waitpid(-1,NULL,WNOHANG);
			if (wpid == -1)
			{
				printf ("woyapshuijiao\n");
				break;
			}
			else if (wpid >0)
			{
				printf ("waitpid wpid = %d\n",wpid);
			}
		}
		while(1)
		{
			sleep(1);
		}
	}
	return 0;
}
