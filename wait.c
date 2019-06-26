#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main ()
{
	pid_t pid = fork ();
	if (pid == 0)
	{
		printf ("i am child,mypid=%d,ppid=%d\n",getpid(),getppid());
		sleep(2);
	}
	else if (pid >0 )
	{
		printf ("i am father \n");
		pid_t wpid = wait (NULL);
		//阻塞等待子进程退出，子进程不退出，父进程不继续，等子进程睡眠两秒钟之后父进程进行打印
		//wpid获得退出进程的pid
		//子进程退出后父进程才进入循环休眠状态
		printf ("wait ok,wpid=%d,pid=%d\n",wpid,getpid());
		while (1)
		{
			sleep(1);
		}
	}
	return 0;
}

