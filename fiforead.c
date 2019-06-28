#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
int main (int argc , char *argv[])
{
	if (argc != 2 )
	{
		printf ("./out fifoname\n");
		return -1;
	}
	int fd =open(argv[1],O_RDONLY);
	char buf[1000];
	int ret = read(fd,buf,sizeof(buf));
	if (ret > 0)
	{
		printf ("%s",buf);
	}
	close(fd);
	return 0;
}



