#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void * thr1(void *arg)
{
	while(1)
	{
		//先上锁
		pthread_mutex_lock(&mutex); 
		printf ("hello");
		printf ("world\n");
		//解锁
		pthread_mutex_unlock(&mutex);
		sleep(1);
		//这里睡眠一秒的原因是，如果一个线程进行这个操作的时候
		//虽然有加锁解锁但是很难失去资源，类似于我们小时
		//拿手捂着一个东西让别人去抢，别人很难抢到
	}
}
void *thr2 (void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex); 
		printf("HELLO");
		printf("WORLD\n");
		pthread_mutex_unlock(&mutex); 
		sleep(1);
	}
}
int main ()
{
	//创建两个线程，分别执行不同的函数
	pthread_t tid[2];
	pthread_create(&tid[0],NULL,thr1,NULL);
	pthread_create(&tid[1],NULL,thr2,NULL);
	//分别对两个线程进行回收（阻塞的那种）
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);

	return 0;
}



