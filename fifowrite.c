#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
int main (int argc,char* argv[])
{
	//当前目录下只有一个fifo文件，供不同进程打开
	//打开fifo文件
	if (argc != 2)
	{
		printf ("./a.out fifoname\n");
		return -1;
	}
	int fd = open(argv[1],O_WRONLY);
	if (fd == -1)
	{
		printf ("打开文件失败\n");
		return -2;
	}
	char buf[1000];
	//定义缓冲区
	sprintf(buf,"今夜不让你入睡\n",sizeof(buf));
	//用sprintf函数对缓冲区进行写入
	write(fd,buf,strlen(buf));
	//以写方式打开文件，进行写入
	close(fd);
	return 0;
}
