#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    pid_t p;
    p=fork();
    switch(p){
        case -1: 
            perror("erreur fork");
            exit(1);
        case 0: 
            printf("\t FILS \n");
            break;
        default: printf("PERE \n");
    }
    printf("Aurevoir\n");
}