#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void cat_signal(int num)
{	//这里的num是由捕捉函数传进来的值，这个值表示捕捉到的函数序列号
	printf ("我把%d信号抓住了\n",num);
	sleep(5);
}

int main ()
{
	struct sigaction cat;
	cat.sa_handler = cat_signal;
	cat. sa_flags = 0;
	sigemptyset(&cat.sa_mask);
	//这里我们加上一行代码，就是为了看看临时阻塞到底是个什么东西，我们在这里临时阻塞3号信号ctrl+\

	sigaddset(&cat.sa_mask,3);
	sigaction(2,&cat,NULL);
	while (1)
	{
		printf ("谁能杀我\n");
		sleep (1);
	}
	return 0;
}

