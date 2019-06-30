#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
int main ()
{
	int i=0;
	int pid ,pid3;
	for  (i ;i < 5; i++)
	{
		pid = fork();
		if (pid == 0)
			break;
		if(i == 2)
		{
			pid3 = pid;
		}
		//在这里需要注意一下，这里只有父进程可以运行到break后面这一段代码，子进程在前面都已经退出
		//当父进程创造第三个孩子的时候才会运行到这一段，并且保存住三号子进程的pid，在下来的代码中方便杀死
	}
	
	if (i < 5)
	{
		while (1)
		{
			printf("我是儿子我的pid=%d我父亲进程pid=%d\n",getpid(),getppid());
			sleep(2);
	 	}
	}
	else if (i ==5)
	{
		printf ("我是父进程，我的pid=%d我将要杀死的进程pid=%d\n",getpid(),pid3);
		sleep(5);
		kill(pid3,9);
		while (1)
		{
			sleep(1);
		}
	}
	return 0;
}
