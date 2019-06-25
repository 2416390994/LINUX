#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main (int argc,char * argv[])
{
	if (argc != 2)
	{
		printf ("./filename\n");
		return -1;
	}
	//open一个文件，以写方式打开要是不存在则创建
	int fd  = open(argv[1],O_WRONLY|O_CREAT,0666);
	//lseek拓展文件，设置偏移量也就是拓展大小
	int ret = lseek(fd,1024,SEEK_END);
	//lseek拓展特性必须先写入一次不然不会生效
	write(fd,"a",1);
	//关闭文件描述符
	close(fd);
	return 0;
}
