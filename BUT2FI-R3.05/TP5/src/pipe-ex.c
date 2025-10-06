#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    pid_t pf2;
    pid_t pf1f1;
    pid_t pf1;
    int tube[2];

    // Création du tube : tube[0] = lecture, tube[1] = écriture
    if (pipe(tube) == -1)
    {
        //prror("pipe fonctionne pas");
        exit(1);
    }

    pf1 = fork();
    if (pf1 == 0){
        // Processus Pf1
        pf1f1 = fork();
        if(pf1f1 == 0){
            //Processus Pf1f1 (lecteur)
            close(tube[1]); // ferme écriture
            dup2(tube[0], STDIN_FILENO); // Sorti tube ver stdin  de pf1f1 
            close(tube[0]); // ferme le lecteur

            // Ici il peut lire depuis stdin (venant du pipe)
            pid_t pid_lu;
            while (1)
            {
               if (read(STDIN_FILENO, &pid_lu, sizeof(pid_t)))
               {
                    printf("%d received %d\n", getpid(), pid_lu);
                    sleep(1);
               }
                
            }
             
        }

    }else{
        pf2 = fork();
        if (pf2 == 0){
            //Processus Pf2 (écrivain)
            close(tube[0]); // ferme lecture
	     // je ne dois pas pointer le stdout_FILENO vers le tube sinon printf va ecrire et dans et pas dans 		le terminal
	    //dup2(tube[1], STDOUT_FILENO); // stdout de pf2 vers entrée du tube 
            //close(tube[1]); // ferme l'ecrivin

            // Ici il écrit son PID en boucle
            while (1)
            {
                pid_t pid = getgid();
                if(write(tube[1], &pid, sizeof(pid_t))){
                    printf("%d sent %d\n", pid, pid);
		    sleep(3);
                }
                
            }

        }else{
            close(tube[0]);
            close(tube[1]);
            wait(NULL);
            wait(NULL);
        }
    }   
    return 0;
}
