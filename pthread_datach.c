#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void* thr (void *arg)
{
	printf ("tid=%ld\n",pthread_self());
	sleep(4);
	printf ("tid=%ld\n",pthread_self());
	return NULL;
}

int main ()
{
	pthread_t tid;
	pthread_create(&tid,NULL,thr,NULL);
	pthread_detach(tid);
	//线程分离
	sleep(5);
	//睡眠时间比线程的时间长所以线程运行结束被系统自动回收
	int ret = 0;
	//这里只是为了插卡pthreadd_join的错误信息，因为已经被系统回收，这里回收必定失败
	if ((ret = pthread_join(tid,NULL)) > 0)
	{
		printf("join err:%d,%s\n",ret,strerror(ret));
	}
	return 0;
}
