#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main ()
{
  int ret  = fork();
  if(ret == 0)
  {
    char* argv[] = {"/usr/bin/ls","-l","/",NULL};
    printf("before execl\n");
    execv("/usr/bin/ls",argv) ;//开始运行之后子进程就会去执行ls命令所以下面的代码就不会被执行
  }
  wait(NULL);
  printf("after execl\n");
  return 0;
}
