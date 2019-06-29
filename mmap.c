#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<string.h>
int main ()
{
	int fd = open ("mem.txt",O_RDWR);
	char *men = mmap(NULL,100,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if (men == MAP_FAILED)
	{
		perror("mmap err\n");
		return -1;
	}
	strcpy(men,"YMM");
	munmap(men,100);
	close(fd);
	return 0;
}
