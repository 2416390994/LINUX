#include<stdio.h>
#include<unistd.h>
#include<signal.h>
int main ()
{
	sigset_t  sin,pend;
	//先定义两个信号集
	sigemptyset(&pend);
	//清空信号集，其实这一步有没有影响不大，一个普通进程，信号集本身就为空
	sigaddset(&pend,2);
	sigaddset(&pend,3);
	sigprocmask(SIG_BLOCK,&pend,NULL);
	//以上三行代码表示设置阻塞信号集，将2.3号信号设置为阻塞
	while (1)
	{
		int i = 1; 
		sigpending(&sin);
		//获取未决信号集，sin是未决信号集
		for (i;i<32;i++)
		{
			int ret = sigismember (&sin,i);
			//判断i号信号是在未决信号集中，在表示未处理，未处理返回1，0代表已处理返回0
			if (ret == 1)
				printf ("1");
			else 
				printf ("0");
				//
		}
		printf ("\n");
		sleep(1);
	}
	return 0;
}
