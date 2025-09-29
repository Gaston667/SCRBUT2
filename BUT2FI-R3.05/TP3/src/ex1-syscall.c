#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(){

	//printf("NON");
	write(STDOUT_FILENO,"NON",3);
	if (fork()) {
		//printf("OUI\n");
	write(STDOUT_FILENO,"OUI\n",4);
	}
}
