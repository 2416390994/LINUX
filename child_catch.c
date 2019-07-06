#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
void cat_signal(int num)
{
	pid_t pid = waitpid(-1,NULL,WNOHANG);
	printf ("我被回收了我是%d\n",pid);
}

int main ()
{
	int i = 0;
	for (i ; i < 10;i++)
	{
		pid_t pid = fork();
		if (pid == 0)
			break;
	}
	if (i == 10)
	{
		struct sigaction act;
		act.sa_handler = cat_signal;
		act.sa_flags = 0;
		sigemptyset(&act.sa_mask);
		sigaction(SIGCHLD,&act,NULL);
		while (1)
		{
		sleep(1);
		}
	}else if (i < 10)
	{
		printf ("我是儿子我的pid是%d\n",getpid());
	}
	return 0;
}
