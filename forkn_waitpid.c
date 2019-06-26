#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int main ()
{
	int i;
	int pid;
	for (i;i<5;i++)
	{
		pid = fork();
		if (pid == 0)
		break;
	}
	if (pid ==5)
	{
		printf("i am father \n");
		while(1)
		{
			int a = waitpid(-1,NULL,WNOHANG);
			if (a>0)
			{
				printf ("waitpid =%d\n",a);
			}
			else if (a == -1)
			{
				break;
			}
		}
		while(1)
		{
			sleep(1);
		}
	}
	if (pid < 5)
	{
		printf ("i am child pid = %d\n",getpid());
	}
	return 0;
 }
