#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<string.h>
typedef struct student
{
	int sid;
	char sname[20];
}stu;

int main (int argc,char *argv[])
{
	if (argc!=2)
	{
		printf("./a.out filename\n");
		return -1;
	}
	int fd = open(argv[1],O_RDWR|O_CREAT,0666);
	ftruncate(fd,sizeof(stu));
	//打开文件拓展空间
	stu * ret = mmap(NULL,sizeof(stu),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if (ret == MAP_FAILED)
	{
		perror("mmap err\n");
		return -2;
	}
	int num = 1;
	while(1)
	{
		ret->sid=num;
		sprintf(ret->sname,"杨毛毛---%3d\n",num++);
		//因为只申请了一个结构体的内存所以每次的写入都会覆盖前一次写入的内容
		sleep(1);
	}
	munmap(ret,sizeof(stu));
	close(fd);
	return 0;
}
