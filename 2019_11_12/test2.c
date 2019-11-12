#include"test.hpp"
#include<pthread.h>
//声明一个环形阻塞队列
//因为阻塞队列中已经进行了同步与互斥的操作
//所以这里不再需要操作，直接使用就可以了
BlockingQueue<int > p(100);
void* func1(void* arg)
{
  (void)arg;
  int count = 0; 
  while(1)
  {
    p.push(++count);
    usleep(789789);
  }
  return NULL;
}
void* func2(void* arg)
{
  (void)arg;
  while(1)
  {
    int w = 0;
    p.pop(&w);
    printf("%d\n",w);
    usleep(123123);
  }
  return NULL;
}
int main()
{
  pthread_t tid1,tid2;
  pthread_create(&tid1,NULL,func1,NULL);
  pthread_create(&tid2,NULL,func2,NULL);
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  return 0;
}
