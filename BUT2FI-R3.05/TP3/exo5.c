#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>

#define SIZE 1000

// Fonction simple qui cherche un zéro dans [start .. end]
int search(const unsigned char *t, int start, int end) {
    for (int i = start; i <= end; i++) {
        if (t[i] == 0) {
            return 1;  
        }
    }
    return 0;
}

int main(int argc , char * argv[]) {
    int i, status, process_count, found;
    unsigned char arr[SIZE];
    pid_t p;

    srandom(time(NULL));

    // Ini du tab entre 1 et 255
    for (i = 0; i < SIZE; i++)
        arr[i] = (unsigned char) (random() % 255) + 1;

    // On place un zéro selon l'entrée utilisateur
    printf("Enter a number between 0 and %d: ", SIZE);
    scanf(" %d", &i);
    if (i >= 0 && i < SIZE) arr[i] = 0;

    // On demande a l'utilisateur un nombre entre 1 et 100 pour le nombre de fils
    printf("Enter a number between 1 and 100: ");
    scanf(" %d", &process_count);
    assert(process_count >= 1 && process_count <= 100); 

    int found = 0;
    // Création des fils
    for (int i = 0; i < process_count; i++)
    {
        // Desoupageage du tableau: chaque fils doit chercher dans une partie du tableau
        // Par exemple si process_count = 4, le premier fils cherche dans [0..249], le deuxième dans [250..499], etc.
        // On peut calculer les bornes de chaque partie avec:
        int start = i * (SIZE / process_count);
        int end = (i + 1) * (SIZE / process_count) - 1;
        // Le dernier fils doit aller jusqu'à la fin du tableau
        if (i == process_count - 1) {
            end = SIZE - 1;
        }
        
        p = fork();
        assert(p >= 0); // fork a echoue
        if (p == 0) {
            int res_fils = search(arr, start, end); // le fils cherche dans la partie qui lui est allouée
            exit(res_fils);
        }        
    }
    
    // p = fork();
    // assert(p >= 0);

    // if (p == 0) {
    //     int res_fils = search(arr, 0, SIZE/2 - 1); // le fils cherche dans la première moitié
    //     exit(res_fils);   
    // } 

    for(int i = 0; i < process_count; i++) {
        pid_t pid_fils = wait(&status);
        assert(pid_fils >= 0); // wait a echoue
        if (WEXITSTATUS(status) == 1) {
            found = 1;
        }
    }

    if (found == 1)
        printf("Found !\n");

    return 0;
}
