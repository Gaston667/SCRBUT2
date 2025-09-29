#include <sys/types.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    pid_t p; // en faite c'est juste un int renomer lol
    int status;
     
    p = fork();
    assert(p >= 0); // fork a echoue

    if (p == 0)
    {
        printf("@retour de fork = %d pid = %d ppid = %d\n",p,getpid(),getppid());
        sleep(4);
        exit(2);
    }

    // p > 0
    printf("@retour de fork = %d pid = %d ppid = %d\n",p,getpid(),getppid());
    assert(wait(&status) >= 0); // wait a echoue

    printf("fils mort avec le code %d\n",WEXITSTATUS(status));
    
    execl("/bin/ps", "ps", "-ef", NULL); // je peut remplacer /bin/ps par ps car ps est dans le PATH
    assert(0); // si on arrive ici c'est que execl a echoue
    return 0;
}
