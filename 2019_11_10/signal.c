#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void signedal(int signo)
{
  printf("我是被%d号信号干掉的\n",signo);
}
int main()
{
  for(int  i = 0;i <= 64;++i)
  {  
    signal(i,signedal);
  }
  while(1)
  {
    printf("哈哈\n");
    sleep(1);
  }

  return 0; 
}
