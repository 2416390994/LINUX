#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main ()
{
  pid_t res  = fork();
  if(res > 0)
  {
    printf("我是父亲%d\n",getpid());
    int status = 0;//传入传出参数
    pid_t result = wait (&status);//默认阻塞等待 
    if(status & 0xff)
    {
      //异常终止
      printf("异常终止，信号为%d\n",status & 0x7f);//异常终止的话那就拿到core dump标志后面的七个位表示终止的信号
    }
    else
    {
      //正常终止
      printf("正常终止，退出码为%d\n",(status>>8) & 0xff);
    }
    printf("我等待的儿子是%d\n",result);
  }
  else if(res == 0)
  {
    int count = 3;
    while(count > 0)
    {
      sleep(1);
      --count;
      printf("%d\n",getpid());
    } 
  }
 return 0; 
}

