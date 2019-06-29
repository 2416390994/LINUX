#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
int main ()
{

	int * mem = mmap(NULL,6,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);
	//只需要在第五个参数后面加上一个hong就可以进行匿名映射了，不需要文件
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
	return 0;
}
