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
	//open一个文件	
	int fd  = open(argv[1],O_RDONLY);
	//调整文件读写位置，返回值为文件开头到文件末尾的长度，利用返回值进行查看文件大小
	int ret = lseek(fd,0,SEEK_END);
	printf("this file size is %d\n",ret);
	//关闭文件描述符
	close(fd);
	return 0;
}
