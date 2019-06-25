//进程创建
#include<stdio.h>
#include<unistd.h>
int main ()
{
	printf ("-----head line-----pid=%d\n",getpid());
	int pid = fork();
	if (pid<0){
		printf ("进程创建失败！\n");	
	}else if(pid ==0){
		printf ("-----child line-----pid=%d\n",getpid());
	}else{
		printf ("-----father line-----pid=%d\n",getpid());
	}
	printf ("-----tail line-----pid=%d\n",getpid());
	return 0;
}
