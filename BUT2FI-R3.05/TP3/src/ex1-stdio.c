#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(){

	printf("NON");
	if (fork()) {
		printf("OUI\n");
	}
}
