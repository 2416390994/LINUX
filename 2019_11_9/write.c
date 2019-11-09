#include"myshm.h"
#include<string.h>
int main()
{
  int  ret = CreateShm();
  char* p = (char*) shmat(ret,NULL,0);
  //写入内容
  strcpy(p,"蛤蟆买皮皮");
  
  return 0;
}
