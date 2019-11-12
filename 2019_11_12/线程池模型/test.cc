#include"threadpool.hpp"
//子类继承于父类，子类主要就是重写了父类中的Run函数
class MyTask:public Task
{
public:
  MyTask(int id):id_(id)
  {
    
  }
  ~MyTask()
  {

  }
  void Run()
  {
    printf("id = %d\n",id_);
  } 
private: 
  int id_;
};
//主函数/入口函数
int main()
{
  //初始化线程池对象，初始化10个线程
  Threadpool pool(10);
  //往线程池中添件20个任务
  for(int i = 0; i < 20; ++i)
  {
    pool.AddTask(new MyTask(i));
  }
  return 0;
}
