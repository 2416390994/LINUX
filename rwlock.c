#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
//初始化
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
//pthread_rwlock_t rwlock;
int begin = 1000;
void* thr_write (void* arg)
{
	while(1)
	{
		//加写锁
		pthread_rwlock_wrlock(&rwlock);
		printf ("---%s---%lu---%d\n",__FUNCTION__ ,pthread_self(),++begin);
		usleep(2000);//模拟运行时耗时
		pthread_rwlock_unlock(&rwlock);
		//解锁
		usleep(10000);//解除锁资源，睡眠让其他线程有可乘之机
	}
	return NULL;
}

void* thr_read (void* arg)
{	
	while(1)
	{
		pthread_rwlock_rdlock(&rwlock);
		printf ("---%s---%lu---%d\n",__FUNCTION__ ,pthread_self(),begin);
		usleep(2000);//模拟运行时耗时
		pthread_rwlock_unlock(&rwlock);
		usleep(2000);//解除锁资源，睡眠让其他线程有可乘之机
	}
	return NULL;
}
int main ()
{
	//pthread_rwlock_init(&rwlock,NULL);
	int i = 0;
	pthread_t tid[8];
	//五个线程执行读函数
	for(i;i<5;i++)
	{
		pthread_create(&tid[i],NULL,thr_read,NULL);
	}
	//三个线程执行写函数
	for(i;i<8;i++)
	{
		pthread_create(&tid[i],NULL,thr_write,NULL);
	}
	//线程回收
	for (i = 0;i < 8;i++)
	{
		pthread_join(tid[i],NULL);
	}
	return 0;
}
