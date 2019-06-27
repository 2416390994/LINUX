#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main ()
{
	int fd[2];
	//定义两个文件描述符
	pipe(fd);
	//将两个文件描述符传入系统自动分配
	pid_t pid = fork();
	//创建子进程
	if (pid == 0)
	{
		close(fd[0]);
		//先重定向，再execlp程序替换实现ps命令
		int ret1 = dup2(fd[1],STDOUT_FILENO);
		//标准输出重定向到管道写端
		//返回值：成功会返回新定义的文件描述符
		if (ret1 == 1)
		//若成功则进行ps aux操作，但是内容写到了管道的写端
			execlp("ps","ps","aux",NULL);
		else
		//失败返回-1
			return -1;
	}
	else if (pid > 0)
	{
		close(fd[1]);
		int ret2 = dup2(fd[0],STDIN_FILENO);
		//标准输入重定向到管道读端
		if (ret2 == 0)
			execlp("grep","grep","bash",NULL);
		else
			return -2;
	}
	return 0;
}
