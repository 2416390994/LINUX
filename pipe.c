#include<stdio.h>
#include<unistd.h>
int main ()
{
	int fd[2];
	pipe(fd);
	pid_t pid = fork();
	if(pid == 0)
	{
		sleep(3);
		write(fd[1],"hello\n",10);
	}
	else if(pid > 0)
	{
		int buf[10];
		int ret = read(fd[0],buf,10);
		if(ret > 0)
		{
			write(STDOUT_FILENO,buf,ret);
		}
	}
	return 0;
}

