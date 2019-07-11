#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
//首先定义两个信号量，用来作为传入参数
sem_t black,xfull;
//定义信号量个数
#define _SEM_CNT_ 5
//定义一个数组
int queue[_SEM_CNT_];
int begin = 1000;
//生产者模型
void* thr_producter(void* arg)
{
	int i = 0;
	while(1)
	{
		//先--操作，让生产者这边计数减1，若已经为0 ，则进阻塞等待
		sem_wait(&black);
		printf ("---%s---%lu---%d\n",__FUNCTION__,pthread_self(),begin);
		queue[(i++)%_SEM_CNT_] = begin++;
		//完毕之后让消费者那边计数加1
		sem_post(&xfull);
		sleep(rand()%3);
	}
	return NULL;
}
void* thr_customer(void* arg)
{
	int i = 0;
	int num = 0;
	while(1)
	{
		//在获得资源之前，消费者计数先减1，要是已经为0，则阻塞等待
		sem_wait(&xfull);
		num = queue[(i++)%_SEM_CNT_];
		printf ("---%s---%lu---%d\n",__FUNCTION__,pthread_self(),num);
		//消费完毕之后，提醒生产者计数加1
		sem_post(&black);
		sleep(rand()%3);
	}	
	return NULL;
}
int main ()
{
	//先初始化两个信号量，一个是生产者的，一个是消费者的
	sem_init(&black,0,5);	
	sem_init(&xfull,0,5);		
	//初始化两个线程
	pthread_t tid[2];
	pthread_create(&tid[0],NULL,thr_producter,NULL);
	pthread_create(&tid[1],NULL,thr_customer,NULL);
	//线程回收
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	//信号量摧毁
	sem_destroy(&black);
	sem_destroy(&xfull);
	return 0;
}
