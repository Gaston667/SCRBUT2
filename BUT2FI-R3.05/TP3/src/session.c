#include <stdio.h>
#include <unistd.h>



int main(int argc, char *argv[])
{
	if (fork()){
		printf("session = %d\n",getsid(getpid()));
		while(1);
	} else {
		setsid();
		printf("session = %d\n",getsid(getpid()));
		while(1);
	}
	return 0;
}

