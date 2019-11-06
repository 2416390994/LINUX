#include<stdio.h>
#include<unistd.h>
int main()
{
  const char* label = "/-\\|";
  char buf[1024] = {0};
  int i = 0;
  while(i < 100)
  {
    buf[i] = '#';
    //printf("[%d%%][%c][%s]\r",i,label[i%4],buf);
    if(i < 33)  
      printf("\033[31m[%d%%][%c][%s]\r\033[0m",i,label[i%4],buf);
    else if(i < 66)
      printf("\033[32m[%d%%][%c][%s]\r\033[0m",i,label[i%4],buf);
    
    else
      printf("\033[33m[%d%%][%c][%s]\r\033[0m",i,label[i%4],buf);
    i++;
    fflush(stdout);
    usleep(100*1000);
  }
  printf("\n");
  return 0;
}
