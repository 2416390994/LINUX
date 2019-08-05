#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main  ()
{
	int fd[2];
	char buf[1024];
	int ret = pipe(fd);
	if (ret != 0)
	{
		perror("make pipe error\n");
		return -1;
	}else
	{
			int ret2 = read(0,buf,sizeof(buf));
			if(ret2 != 0)
			{
				write(fd[1],buf,ret2);
			}
			memset(buf,0x00,sizeof(buf));
			read(fd[0],buf,ret2);
			write(1,buf,ret2);
	}
	return 0;
}
