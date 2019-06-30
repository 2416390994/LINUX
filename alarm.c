#include<stdio.h>
#include<unistd.h>
int main ()
{
	alarm(6);
	while (1)
	{
		printf ("我快死了\n");
		sleep(1);
	}
	return 0;
}
