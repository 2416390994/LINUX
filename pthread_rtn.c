#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
void * thr (void *arg)
{
	printf ("i am a thread,tid = %lu\n",pthread_self());
	sleep(5);
	printf ("i am a thread,tid = %lu\n",pthread_self());
	return (void *)100;
	//里面返回一个值，从函数返回值可以看出这里给出的返回值要是void*类型，所以这里进行强转
}
int main ()
{
	pthread_t tid;
	pthread_create(&tid,NULL,thr,NULL);
	void *ret;
	//根据pthread_join函数原型可以知道第二个参数是二级指针所以传入的是一个指针的地址
	//函数原型是int pthread_join(pthread_t thread, void **retval);
	//定义了ret是一个指针，那么**retval就是一个二级指针，代表的就是指针的指针，指针的指针存放的就是指针的地址，所以传参的是传&ret就可以了
	pthread_join(tid,&ret);
	//这里打印的时候要对void*类型的ret进行强转,根据的是函数参数类型
	printf ("ret exit with %d\n",(unsigned long)ret);
	pthread_exit(NULL);
}
