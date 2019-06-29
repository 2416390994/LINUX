#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
int main ()
{
	int fd = open("xxx.txt",O_RDWR|O_CREAT);
	//先打开一个文件，如果这个文件不存在则创建
	int buf[1]={0};
	//无论你是txt文件已经有了，还是open创建出来的，如果文件内部没有数据
	//则无法在内存中进行有效映射
	//所以在这里我进行了写入，保证了内存实现映射
	write(fd,buf,sizeof(buf));
	int * mem = mmap(NULL,6,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if (mem == MAP_FAILED)
	{
		perror("mmap err");
		return -1;
	}
	pid_t pid = fork();
	if (pid == 0)
	{
		*mem = 1001;
		printf ("我是儿子 *mem=%d\n",*mem);
		sleep(3);
		printf ("我是儿子 *mem=%d\n",*mem);
	}
	else if (pid > 0)
	{
		sleep(1);
		printf ("我是父亲 *mem=%d\n",*mem);
		*mem = 10;
		printf ("我是父亲 *mem=%d\n",*mem);
		wait(NULL);
		printf ("我把我儿子已经回收了\n");
	}
	munmap(mem,6);
	//释放内存空间
	remove("xxx.txt");
	//还有一点就是文件在父子进程中只起到了桥梁的作用，所以要考虑删除文件
	close(fd);
	return 0;
}
