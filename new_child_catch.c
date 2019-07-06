#include<stdio.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>
void cat_signal(int num)
{	
	pid_t pid;
	while((pid =waitpid(-1,NULL,WNOHANG))>0)
	{
		printf ("我是子进程%d，我退出了\n",getpid());
	}
}
int main ()
{
	int i = 0;
	pid_t pid;
	sigset_t myit,old;
	sigemptyset(&myit);
	sigaddset(&myit,SIGCHLD);
	sigprocmask(SIG_BLOCK,&myit,&old);
	for (i ;i < 10;i++)
	{
		pid = fork();
		if (pid == 0)
			break;
	}
	if (i == 10)
	{	
		sleep(2);
		struct sigaction act;
		act.sa_handler = cat_signal;
		act.sa_flags = 0;
		sigemptyset(&act.sa_mask);
		sigaction(SIGCHLD,&act,NULL);
		sigprocmask(SIG_SETMASK,&old,NULL);
		while (1)
		{
			sleep(1);
		}
	}else if (i < 10)
	{
		printf ("我是子进程%d\n",getpid());
	}

	return 0;
}
