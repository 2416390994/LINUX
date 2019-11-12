#pragma once 
#include"test.hpp"
//父类，给出了一个虚的析构函数，和一个虚的Run函数
//虚析构是为了用父类的指针去析构子类的对象
//虚的Run函数为的就是让子类进行重写，执行子类的操作
class Task
{
public:
  virtual ~Task()
  {

  }
  virtual void Run()
  {
    printf("我的出现只是为了让子类重写\n");
  }
};

//线程池类
class Threadpool
{
public:
  Threadpool(int n)
    :queue_(100)
     ,worker_count_(n)
  {  
    for(int i = 0;i < worker_count_; ++i)
    {
      pthread_t tid;
      pthread_create(&tid,NULL,ThreadEntry,this);
      workers_.push_back(tid);
    }
  }
  ~Threadpool()
  {
    //for(size_t i = 0;i < workers_.size();++i)
    //{
    //  pthread_cancel(workers_[i]);
   // }
    for(size_t i = 0;i<workers_.size();++i)
    {
      pthread_join(workers_[i],NULL); 
    }
  }
  void AddTask(Task* task)
  {
    queue_.push(task);  
  }
private:
  //一个阻塞队列
  BlockingQueue<Task*> queue_; 
  //记录工作线程数量
  int worker_count_;
  //记录每个创建的线程的tid因为最后还要回收线程
  vector<pthread_t> workers_;

  static void* ThreadEntry(void* arg)
  {
    Threadpool* pool = (Threadpool*)arg;
    while(true)
    {
      Task* task = NULL;
      pool->queue_.pop(&task);
      task->Run();
      delete task;
    }
  }
};
