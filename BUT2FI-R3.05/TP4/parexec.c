#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    if (argc < 3) {
        printf("Usage: %s <nombre>\n", argv[0]);
        return 1;
    }

    pid_t p= getpid();
    int nbr_proc = argc - 2;

    for(int i=0; i < nbr_proc; i++){
        p = fork();
        if (p == 0)
        {
            execl(argv[1], argv[1], argv[i+2], NULL);
            assert(0);
        }
    }
    for (int  i = 0; i < nbr_proc; i++){
        wait(NULL);        
    }
    
    return 0;
}
