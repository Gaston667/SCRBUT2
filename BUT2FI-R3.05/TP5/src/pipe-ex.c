#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pf2;
    pid_t pf1f1;
    pid_t pf1;
    int tube[2];

    // Création du tube : tube[0] = lecture, tube[1] = écriture
    if (pipe(tube) == -1)
    {
        prror("pipe fonctionne pas");
        exit(1);
    }

    pf1 = fork();
    if (pf1 == 0){
        // Processus Pf1
        pf1f1 = fork();
        if(pf1f1 == 0){
            //Processus Pf1f1 (lecteur)
            close(tube[1]); // ferme ecrivain
            // Je conecte la sorti du tube à l'entrer du proc stdin
            dup2(tube[0], STDIN_FILENO);
            close(tube[0]); // ferme l'ecrivin
        }

    }else{
        pf2 = fork();
        if (pf2 == 0){
            // Enfant 1 : écriture
            close(tube[0]); // ferme lecture
            // Je conecte l'entrer du tube à la soti du proc stdout
            dup2(tube[1], STDOUT_FILENO);
            close(tube[1]); // ferme l'ecrivin

        }else{
            close(tube[0]);
            close(tube[1]);
            wait(NULL);
            wait(NULL);
        }
    }   
    return 0;
}
