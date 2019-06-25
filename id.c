#include<stdio.h>
#include<unistd.h>
int main ()
{
	printf("begin...\n");
	pid_t pid = fork();
	if (pid == 0)
	{
		printf ("我是儿子\n");
		while(1)
		{
			printf ("laji.....\n");
			sleep(1);
		}
	}
	else if(pid > 0)
	{
		printf ("ownpid=%d\nchiledpid=%d\nfatherpid=%d\n",getpid(),pid,getppid());
		while(1)
		{
			sleep(1);
		}
	}
	return 0;
}
