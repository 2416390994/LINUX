#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void * thr (void *arg)
{
	unsigned long num =(unsigned long)  arg;
	printf ("为了新中国,tid =%lu\n",pthread_self());
	return (void*)num;
}
int main ()
{
	pthread_t tid[5];	
	int i = 0;
	for (i;i<5;i++)
	{
		pthread_create(&tid[i],NULL,thr,(void*)i);
	}
	for (i = 0;i < 5;i++)
	{
		void *ret;
		pthread_join(tid[i],&ret);
		printf ("i = %d,ret = %ld\n",i,(unsigned long)ret);
	}
	//打印线程退出信息
	return 0;
}

