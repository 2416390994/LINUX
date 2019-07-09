#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void* thr (void* arg)
{
	while (1)
	{
		printf ("我是创建出来的线程tid=%d\n",pthread_self());
		sleep (1);
	}
	pthread_exit((void*)100);
}

int main ()
{
	//创建线程
	pthread_t tid;
	pthread_create(&tid,NULL,thr,NULL);
	//杀死线程
	sleep(5);
	pthread_cancel(tid);
	//线程回收
	void *ret;
	pthread_join(tid,&ret);
	printf ("%d\n",(unsigned long)ret);
	return 0;
}
