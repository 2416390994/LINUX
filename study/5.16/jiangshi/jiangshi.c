//僵尸进程
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main ()
{
	int pid = fork();
	if (pid<0){
		return -1;
	}else if(pid ==0){
		sleep(5);
		exit(0);
	}
	while (1){
		sleep(1);
	}
	return 0;
}
