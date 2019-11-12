#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<vector>
#include<pthread.h>
#include<stdlib.h>
using namespace std;
pthread_mutex_t mutex; //定义一把锁
pthread_cond_t cond; //定义一个条件变量
vector<int> vec;
void* func1(void* arg)
{
  (void)arg;
  int g_count = 0;
  sleep(3);
  while(1)
  {
    pthread_mutex_lock(&mutex);
    vec.push_back(++g_count);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
    usleep(789789);
  }
  return NULL;
}
void* func2(void* arg)
{
  (void)arg;
  printf("123\n");
  while(1)
  {
    printf("456\n");
    pthread_mutex_lock(&mutex);
    if(vec.empty())
    {
      printf("789\n");
      pthread_cond_wait(&cond,&mutex);
    }
   if(!vec.empty())
   {

    //pthread_mutex_lock(&mutex);
    int ret = vec.back();
    vec.pop_back();
    printf("%d\n",ret);
    pthread_mutex_unlock(&mutex);
    usleep(123123);
  }
  }
  return NULL;
}
int main()
{
  pthread_t tid[4];
  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&cond,NULL);

  pthread_create(&tid[0],NULL,func1,NULL);
  pthread_create(&tid[1],NULL,func1,NULL);
  pthread_create(&tid[2],NULL,func2,NULL);
  pthread_create(&tid[3],NULL,func2,NULL);

  for(int i = 0;i< 4 ;++i)
  {
    pthread_join(tid[i],NULL);
  }
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  return 0;
}
