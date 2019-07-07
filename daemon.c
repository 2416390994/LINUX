#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<time.h>
#include<signal.h>
#include<fcntl.h>
#include<string.h>
#define filename  "%s/laji.%ld"

void touchfile(int num)
{
	 char *home = (getenv("HOME"));
	 char strfilename[250]={0};
	 sprintf(strfilename,filename,home,time(NULL));
	 int fd = open (strfilename,O_RDWR|O_CREAT,06666);
	 if (fd < 0)
	 {
	 	perror("open err");
		exit(1);
	 }
	close(fd);
}
int main ()
{
	//创建子进程，父进程退出
	//当会长
	//设置权限掩码
	umask(0);
	///关闭文件描述符
	//close（0），close（1），close（2）
	//执行核心逻辑,每隔一分钟在家目录下创建一个文件
	struct itimerval myit =  {{60,0},{1,0}};
	setitimer (ITIMER_REAL,&myit,NULL);
	struct sigaction act;
	act.sa_flags = 0;
	act.sa_handler = touchfile;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM,&act,NULL);
	while(1)
	{
			
	}
	//切换目录,切换到家目录
	chdir(getenv("HOME"));
	//退出
	return 0;
}
