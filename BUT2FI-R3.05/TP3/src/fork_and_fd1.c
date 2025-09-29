#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include<assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define msg1 "je suis le pere"
#define msg2 "je suis le fils !!!"

int main(int argc,char * argv[]){

	int outfd;
	pid_t p;

	if (argc != 2){

		printf("%s file\n",argv[0]);
		exit(1);
	}

	//p=fork();
	outfd = open(argv[1],O_WRONLY|O_CREAT,0644);
	assert(outfd >= 0);
	p=fork();
	switch(p){
		case (pid_t)-1 : 
			perror(NULL);
			exit(2);

		case (pid_t)0 :
			write(outfd,msg2,strlen(msg2));
			break;
		default : 
			write (outfd,msg1,strlen(msg1));
			break;
	}
	close(outfd);
}
