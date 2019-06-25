#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<error.h>
int main (int argc,char *argv[],char *env[])
{
	while(1)
	{
		char buf[1024]={0};
		printf ("[user@localhost]$");
		fflush(stdout);
		if (scanf("%[^\n]%*c",buf)!=1)
		{ 
			getchar();
			continue;
		}
		//printf ("buf:[%s]\n",buf);
                  int argc=0;
                  char *argv[32];
                  char *ptr=buf;
                  while (*ptr!='\0')
                  {       
                  if (!isspace(*ptr))
                          {
                          argv[argc]=ptr;
                          argc++; 
                          while (!isspace(*ptr) && *ptr!='\0')
                          {
                                  ptr++;
                          }
                          *ptr = '\0';
                         // printf ("argv[%d]=[%s]\n",argc,argv[argc-1]);
                          }
		       ptr++;
	       	   }
		argv[argc] = NULL;
		int pid=fork();
		if (pid < 0)
		{
			perror("fork error");
			return -1;
		} else if (pid == 0)
		{
			execvp(argv[0],argv);
			exit(-1);
		}
		wait(0);
	}
	return 0;
}
