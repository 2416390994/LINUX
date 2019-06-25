#include<stdio.h>
#include<unistd.h>
int main ()
{
	execlp("ls","ls","-l","-a",NULL);
	//第一个ls代表文件，他将回去PATH指定的环境变量下面去找
	//第二个ls代表argv[0],紧接着是argv[1],以此类推，可变参数。
	execl("bin/ls","ls","-l",NULL);
	perror("exec error");
	return 0;
}
