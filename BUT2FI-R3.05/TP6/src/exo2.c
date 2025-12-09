#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define NUM_THREADS 16

struct  segment
{
    int debut_segment;
    int fin_segment;
    int S;
}typedef seg;



void * thread(void * thread_id) {
	
}

int main(int argc, const char *argv[]) {
    pthread_t threads[atoi(argv[1])];
    seg kouami;

    for (int i = 0; i < atoi(argv[1]); i++){
        seg kouami;
        kouami.debut_segment = 0;
        kouami.fin_segment = atoi(argv[1]);
        assert(pthread_create(&thread[i],NULL, thread, (void *) &kouami) == 0);
    }
    

	return EXIT_SUCCESS;
}
