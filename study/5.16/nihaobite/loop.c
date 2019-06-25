#include <stdio.h>
#include<unistd.h>
int main ()
{
	//pid_t getpid(void);
	//返回调用进程的ID
	pid_t pid = getpid();
	while(1)
	{
		printf ("hello,bit!!---pid=%d\n",pid);
		sleep(1);
	}
	return 0;
}
