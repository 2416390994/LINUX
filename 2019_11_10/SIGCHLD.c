#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
int main ()
{
  signal(17,SIG_IGN);
  int ret = fork();
  if(ret > 0)
    while(1)
    {
      sleep(1);
    }
  else if(ret == 0)
    return 0;
  else
    perror("fork");
  return 0;
}
