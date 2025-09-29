#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    if (argc < 2) {
        printf("Usage: %s <nombre>\n", argv[0]);
        return 1;
    }

    pid_t p= getpid();
    int n = atoi(argv[1]);

    printf("%d:debut\n",p);

    for(int i=n; i > 0; i--){
        printf("%d:%d\n",p, i);
        sleep(1);
    }

    printf("%d:fin\n",p);
    
    return 0;
}
