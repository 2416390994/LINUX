#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main (int argc,char * argv[])
{
	
	int fd = open(argv[1],O_RDWR|O_CREAT,0666);
	write(fd,"我今天好累\n",20);
	int a = lseek(fd,0,SEEK_END);
	printf("%d\n",a);
	char buf[1024];
	int ret = read(fd,buf,sizeof(buf));
	if(ret)
	{
		write(1,buf,ret);
	}
	close(fd);
	return 0;
}
