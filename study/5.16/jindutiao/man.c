#include<stdio.h>
#include<unistd.h>
int main ()
{
	char a[10]={0};
	int i=0;
	for (i;i<10;++i)
	{
		a[i]='-';
		printf ("%s\r",a);
		fflush(stdout);
		usleep(100000);
	}
	return 0;
}
