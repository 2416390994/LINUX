#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<signal.h>
void catch_sig(int num)
{
	printf ("cat %d sig\n",num);
}
int main ()
{
	struct sigaction act;
	act.sa_flags = 0;
	act.sa_handler = catch_sig;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM,&act,NULL);
	struct itimerval myit ={{3,0},{3,0}};
	setitimer(ITIMER_REAL,&myit,NULL);
	while (1)
	{
		printf ("你好\n");
		sleep(1);
	}

	return 0;
}
