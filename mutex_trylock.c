#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
pthread_mutex_t mutex;
//定义初始化传入参数，因为要被众多线程共用
void * thr (void *arg)
{	
	while(1)
	{
		//加锁
		pthread_mutex_lock(&mutex);
		printf ("菜狗\n");
		sleep(30);
	}
	return NULL;
}
int main ()
{
	//初始化
	pthread_mutex_init(&mutex,NULL);
	//创建线程，执行函数
	pthread_t tid;
	pthread_create(&tid,NULL,thr,NULL);
	//睡眠一秒钟让创建的线程占用锁资源
	sleep(1);
	while(1)
	{
		//尝试加锁,但是会失败，因为线程占用着锁资源，主线程无法加锁
		int ret = pthread_mutex_trylock(&mutex);
		if(ret > 0)
		{
			printf ("%d,%s\n",ret,strerror(ret));
		}
		sleep(1);
	}
	return 0;
}
