#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
void catchsignal(int number)
{
	printf("我是%d信号，我被抓住了\n",number);
}
int main ()
{
	struct sigaction act;
	act.sa_handler = catchsignal;
	act.sa_flags = 0;
	sigemptyset (&act.sa_mask);
	sigaction (SIGALRM,&act,NULL);
	struct itimerval myit ={{3,0},{3,0}};
	setitimer(ITIMER_REAL,&myit,NULL);
	while (1)
	{
		printf ("谁能杀我\n");
		sleep(1);
	}
	return 0;
}
