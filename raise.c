#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
int main ()
{
	printf ("我马上自杀\n");
	sleep(2);
	raise(9);
	//这里一般可以使用信号的宏来杀死进程
	return 0;
}
