#include<iostream>
#include<vector>
#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
//用数组实现一个阻塞队列
using namespace std;
template<typename T>
class BlockingQueue 
{
public:
  BlockingQueue(int MAX_size)
    :MAX_size_(MAX_size)
     ,head_(0)
     ,tail_(0)
     ,size_(0)
     ,queue_(MAX_size)  //veccto<int> vec(100);意思就是初始化100个空间里面全为0
  {
    sem_init(&lock_,0,1);  //用二元信号量来表示锁
    sem_init(&elem_,0,0);  //这个信号量是为了实现同步，表示的是有效元素的个数
    sem_init(&blank_,0,MAX_size); //这个信号量也是为了实现同步，表示的是队列中还有的空格子数
  }
  //释放掉申请的锁资源
  ~BlockingQueue()
  {
    sem_destroy(&lock_);
    sem_destroy(&elem_);
    sem_destroy(&blank_);
  }
  //每次弹出一个元素的时候
  //先给有效元素信号量-1
  //再上锁开始操作
  //然后再释放锁
  //然后再给空格子信号量+1
  //因为外界需要打印，所以这里就返回一个值
  T pop(T* p)
  {
    sem_wait(&elem_);
    sem_wait(&lock_);
    *p = queue_[head_];
    head_++;
    size_--;
    sem_post(&lock_);
    sem_post(&blank_);
    return *p;
  }
  //每次要插入元素的时候
  //先给空格子信号量-1
  //在上锁
  //再释放锁
  //再给有效元素信号量+1
  void push(T& p)
  {
    sem_wait(&blank_);
    sem_wait(&lock_);
    queue_[tail_] = p;
    tail_++;
    size_++;
    sem_post(&lock_);
    sem_post(&elem_);
  }
private:
  vector<T> queue_;
  int head_; //记录下一个弹出的位置
  int tail_; //记录下一个插入的位置
  int MAX_size_;  //数组最大长度
  int size_;
  sem_t lock_;   //将一个信号量当作互斥锁来使用，二元信号量和互斥锁差不多一份资源非0即1，所以和互斥锁一样
  sem_t elem_; //下面的两个信号量是实现阻塞的，一个标记有多少空格
  sem_t blank_; //一个表示有多少有效元素
};
