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

	int infd,outfd;
	ssize_t nbread;
	char buf[1];
	pid_t p;

	if (argc != 3){

		printf("%s infile outfile\n",argv[0]);
		exit(1);
	}

	infd = open(argv[1],O_RDONLY);
	assert(infd >= 0);
	outfd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
	assert(outfd >= 0);

	//p=fork(); // <- decommentez cette ligne

	while(1){
	
	nbread=read(infd,buf,sizeof(buf));
	if (nbread <=0 ) break;
	write(outfd,buf,sizeof(buf));

	}


	close(infd);
	close(outfd);
}
