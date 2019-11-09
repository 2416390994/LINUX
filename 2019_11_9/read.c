#include"myshm.h"
int main()
{
  //1.创建共享内存，或者打开已经创建好的共享内存
  //ret不是别的就是我们已经打开的共享内存的句柄，可以通过句柄去使用共享内存
  //查看CreateShm，我们刚开始在创建共享内存的时候就已经把大小指定好了
  int ret = CreateShm();
  //2.附加到共享内存上
  char* p =(char*)shmat(ret,NULL,0);
  //将本进程附加到共享内存上，返回的就是共享内存的指针
  //直接就可以使用了，这块内存和malloc创建的内存差不多，可以直接使用
  printf("[read]%s\n",p); 
  return 0;
}
