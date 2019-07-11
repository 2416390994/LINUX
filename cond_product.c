#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int begin = 1000;
//先定义一个链表来模仿生产者
typedef struct _prodinfo
{
	int num;
	struct _prodinfo* next;
}prodinfo;
//定义头节点指向空
prodinfo* head = NULL;
//生产者模型
void* thr_producter(void *arg)
{
	while(1)
	{
		//生产者先申请一块空间，并向空间里面填充数据
		prodinfo* prod = (prodinfo*)malloc(sizeof(prodinfo));
		prod->num = begin++;
		//打印信息
		printf ("---%s---%lu----%d\n",__FUNCTION__,pthread_self(),prod->num);
		//加锁
		pthread_mutex_lock(&mutex);
		//头插
		prod->next = head;
		head = prod;
		//解锁
		pthread_mutex_unlock(&mutex);
		//发起通知
		pthread_cond_signal(&cond);
		sleep(rand()%4);
	}
	return NULL;
}
//消费者模型
void* thr_customer(void* arg)
{
	//定义一个结构体变量
	prodinfo* prod = NULL;
	while(1)
	{
		//加锁
		pthread_mutex_lock(&mutex);
		//如果筐子里面没有饼，则进行变量阻塞
		if (head == NULL)
		{	
			pthread_cond_wait(&cond,&mutex);
		}
		//头删，模仿拿走饼
		prod = head;
		head = head->next;
		//打印拿出的信息
		printf ("---%s---%lu----%d\n",__FUNCTION__,pthread_self(),prod->num);
		//解锁
		pthread_mutex_unlock(&mutex);
		//释放内存
		free(prod);
		sleep(rand()%4);
	}
	return NULL;
}
int main ()
{
	//创建两个线程
	pthread_t tid[2];
	pthread_create(&tid[0],NULL,thr_producter,NULL);
	pthread_create(&tid[1],NULL,thr_customer,NULL);	
	//回收线程
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	//摧毁互斥锁，和条件变量锁
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}
