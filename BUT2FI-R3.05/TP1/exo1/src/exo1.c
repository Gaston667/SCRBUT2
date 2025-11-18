/* adresses virtuelles d'un processus */
#include<stdio.h>
#include<sys/types.h>
#include <sys/time.h>
#include<unistd.h>
#include<stdlib.h>

int t[1000] = {[0 ... 999] = 2};// tableau global 

int main(int argc, char * argv[]) // argc variable local
{
	int i=3; // variable local
	static int j = 3; // variable static 
	char * m = (char*)malloc(1); // c'est pointeur sur memoire
	printf("je suis le pid %d\n\n",getpid());
	/* ------- Affichage des adresses --------*/
	printf("main\t\t=\t%p\n",main);
	printf("gettimeofday\t=\t%p\n",gettimeofday);
	printf("&argc\t\t=\t%p\n",&argc);
	printf("&i\t\t=\t%p\n",&i);
	printf("&j\t\t=\t%p\n",&j);
	printf("t\t\t=\t%p\n",t);
	printf("m\t\t=\t%p\n",m);

	getchar();
} 