#include<stdio.h>
#include<sys/time.h>
#include<unistd.h>
//函数原型，照着函数原型定义函数
//unsigned int alarm(unsigned int seconds);
//实现alarm函数最后直接在main中调用就可以了
unsigned int myalarm (unsigned int seconds)
{
	struct itimerval cat ={{0,0},{0,0}};
	struct itimerval old ={{0,0},{0,0}};
	//对照着setitimer 函数来对结构体进行设置
	cat.it_value.tv_sec = seconds;
	//将时间传进来
	setitimer(ITIMER_REAL,&cat,&old);
	printf ("%ld,%ld\n",old.it_value.tv_sec,old.it_value.tv_usec);
	return old.it_value.tv_sec;
}


int main ()
{
	int ret = 0;
	ret = myalarm(5);
	sleep(1);
	ret = myalarm(5);
	printf ("%d\n",ret);
	sleep (2);
	ret = myalarm(2);
	printf ("%d\n",ret);
	while (1)
	{
		printf ("谁能杀我\n");
		sleep(1);
	}
	return 0;
}
