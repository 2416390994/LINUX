#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>
void cat (int num)
{
	printf ("今晚月色好美%d\n",num);
}
int main ()
{	
	signal(14,cat);
	//在有14号信号产生的时候调用cat函数，这个函数的类型必须是void （*）（int）
	//因为在man signal 有一个typedef声明，来声明这个函数
	//如果没有这个捕捉函数的话，那么进程将被14号进程终止，但是有了捕捉信号之后，14号
	//信号将会被捕捉，去打印cat的内容，那么本进程将不会被终止
	struct itimerval myit = {{3,0},{5,0}};
	setitimer(ITIMER_REAL,&myit,NULL);
	while (1)
	{
		printf ("who can kill me \n");
		sleep (1);
	}
	return 0;
}
