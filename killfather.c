#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>
#include<stdlib.h>
int main ()
{
	int i = 0;
	for (i; i < 5 ;i++ )
	{
		pid_t pid = fork();
		if (pid == 0)
		break;
	}
	if (i == 3)
	{
		printf ("我将在5s后杀了我爹\n");
		sleep(5);
		kill(getppid(),SIGKILL);
		while (1)
		{
			sleep(1);
		}
	}else if(i == 5)
	{
		while(1)
		{
			printf ("我将在5s后被我第4个儿子是杀死\n");
	    	sleep(1);
		}
	}
	return 0;
}
