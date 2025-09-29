#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    if (argc < 4) {
        printf("Usage: %s <./proc> <N> <nombre>\n", argv[0]);
        return 1;
    }
    // initialisation
    int const N = atoi(argv[2]);
    pid_t p= getpid();
    printf("JE SUIS LE PERE %d.\n", p);
    int nbr_proc = argc - 3;
    int nbr_actif = 0;
   

  

    for(int i=0; i < nbr_proc; i++){
        while (nbr_actif == N)
        {
            // pour la recuperation les fils en cour d'ecution
            for (int  i = 0; i <= nbr_actif; i++){
                wait(NULL);        
            }
            nbr_actif--;
        }
        p = fork();
        if (p == 0){
            execl(argv[1], argv[1], argv[i+3], NULL);
            assert(0);
        }
        nbr_actif ++;
    }   

    // pour la recuperation les fils restant
    for (int  i = 0; i < nbr_proc; i++){
        wait(NULL);        
    }

    return 0;
}
