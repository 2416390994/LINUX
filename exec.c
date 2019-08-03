#include<stdio.h>
#include<unistd.h>
int main ()
{
	char * const argv[] = {"ps","-l",NULL};
	char * const envp[] = {"PATH=/bin:/usr/bin","TERM=console",NULL};
	execlp("ps","ps","-l",NULL);
	execv("/bin/ps",argv);
	execl("/bin/ps","ps","-l",NULL);
	execle("/bin/ps","ps","-l",NULL,envp);
	execve("/bin/ps",argv,envp);
	execvp("ps",argv);
	return 0;
}
