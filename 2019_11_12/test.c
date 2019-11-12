#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
void* func1(void* arg)
{
  (void)arg;
  while(1)
  {
    pthread_cond_signal(&cond);
    printf("传球\n");
    usleep(789789);
  }
  return NULL;
}
void* func2(void* arg)
{
  (void)arg;
  while(1)
  {
    pthread_cond_wait(&cond,&mutex);
    printf("扣篮\n");
    usleep(123123);
  }
  return NULL;
}
int main()
{
  pthread_t tid[2];
  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&cond,NULL);
  pthread_create(&tid[0],NULL,func1,NULL);
  pthread_create(&tid[1],NULL,func2,NULL);
    
  pthread_join(tid[0],NULL);
  pthread_join(tid[1],NULL);
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  
  
  return 0;
}
