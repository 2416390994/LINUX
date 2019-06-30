#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
int main ()
{
	struct itimerval  old_value = {{0,0},{3,0}};
	setitimer(ITIMER_REAL,&old_value,NULL);
	//第二个参数，因为是实参传的是地址，形参用*接受，因为函数定义是*，所以这里传参传&
	while(1)
	{
		printf ("谁能杀我\n");
		sleep(1);
	}
	return 0;
}


