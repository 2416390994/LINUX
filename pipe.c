//pipe管道简单实现 
#include<stdio.h>
#include<unistd.h>
int main ()
{
	int fd[2];
	//定义两个文件描述符
	pipe(fd);
	//把这两个文件描述符传到pipe管道函数中去
	pid_t pid = fork();
	//产生子进程
	if (pid == 0)
	{
		sleep(3);
		//这里就算子进程睡上3秒父进程也不会先于子进程退出
		//因为在父进程中read函数默认是阻塞等待
		write(fd[1],"hellword\n",10);
		//fd[1]指管道的写端
	}
	else if (pid > 0)
	{
		char buf[12];
		int ret = read(fd[0],buf,sizeof (buf));
		//fd[0]代表读端，从读端读取数据
		if (ret > 0)
		{
			write(STDOUT_FILENO,buf,ret);
			//读完之后把读到的内容输入到屏幕上
		}
	}
	return 0;

