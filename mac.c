#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>

int main ()
{
	//close(1);
	int fd = open("1.log",O_CREAT|O_TRUNC|O_WRONLY,0644);
	//char buf[100] = "我好累\n";
	int ret = write(fd,"123456\n",10);
	printf("%d\n",ret);
	//printf("hello \n");
	//fflush(stdout);
	//close(fd);
	char buf2[100];
	int ret1 = read(fd,buf2,ret);
	printf("%d\n",ret1);
    close(fd);
	return 0;
}
