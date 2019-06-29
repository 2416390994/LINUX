#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/mman.h>
typedef struct student
{
	int sid;
	char sname[20];
}stu;

int main (int argc,char* argv[])
{
	int fd = open (argv[1],O_RDWR);
	int length = sizeof (stu);
	stu *ret = mmap(NULL,length,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if (ret == MAP_FAILED)
	{
		perror("mmap err");
		return -1;
	}
	while (1)
	{
		printf ("sid = %d,sname=%s\n",ret->sid,ret->sname);
		sleep(1);
	}
	munmap(ret,length);
	close(fd);
	return 0 ;
}
