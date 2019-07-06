#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>
void catch_sig(int number)
{
	printf("我是%d信号，我被抓住了\n",number);
}//定义一个行为函数，用来捕捉到信号的时候执行
int main ()
{
	//定义一个结构体变量，这个变量是作为参数传入sigaction函数，在函数外部需要进行初始化，具体结构体内容参考man sigaction
	struct sigaction act;
	//初始化结构体成员
	act.sa_flags = 0;
	act.sa_handler = catch_sig;
	//函数会设置一个临时阻塞集，为了以防万一，在这里我们清空一下信号集
	sigemptyset(&act.sa_mask);
	//执行捕捉函数，捕捉14号信号，捕捉到信号就去执行结构体中的函数动作，进程将不会被终止
	sigaction(SIGALRM,&act,NULL);
	//设置闹钟，定义结构体变量，并且进行初始化
	struct itimerval myit ={{3,0},{4,0}};
	//执行闹钟，闹钟只会发送14号信号给当前进程，时间周期是，每隔三秒发送一次，第一次发送的时间是4秒后
	setitimer(ITIMER_REAL,&myit,NULL);
	while (1)
	{
		printf ("谁能杀我\n");
		sleep(1);
	}
	return 0;
}
