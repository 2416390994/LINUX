#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
#include<sys/time.h>
#define pthread_size  2
#define MAX  100000000
void change(int* p,int begin,int end)
{
  for(int i = begin ;i < end;++i)
  {
    p[i] = p[i] * 2;
  }
}
typedef struct ARG
{
  int begin;
  int end;
  int *p;
}ARG;
void* Created_thread(void* arg)
{
  ARG* cc = (ARG*)arg;  
  change(cc->p,cc->begin,cc->end);
  return NULL;
}
int gettime()
{
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec*1000000 + tv.tv_usec;
}
int main()
{
  srand(time(NULL));
  int* p = (int *)malloc(sizeof(int)*MAX);
  int i; 
  for(i = 0; i < MAX;++i)
  {
    p[i] = i;
  }
  pthread_t tid[pthread_size] = {0};
  ARG arg[pthread_size];
  int c = 0;
  for(i = 0; i < pthread_size;++i)
  {
    arg[i].begin = c;
    arg[i].end =c + (MAX / pthread_size);
    arg[i].p = p;
    c = c + (MAX / pthread_size);
  }
  int64_t  begin = gettime(); 
  for(i = 0 ;i < pthread_size;++i)
  {
    pthread_create(&tid[i],NULL,Created_thread,&arg[i]);
  }
  pthread_join(tid[0],NULL);
  pthread_join(tid[1],NULL);
  int64_t end = gettime();
  printf("%ld\n",end - begin);
  return 0;
}
