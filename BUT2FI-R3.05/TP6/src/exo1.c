#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define NUM_THREADS 16

void *thread(void *thread_id) {
	int id = *((int *) thread_id);
	printf("Hello from thread %d\n", id);
    // Si malloc on free thread_id
	return NULL;
}

int main() {
	pthread_t threads[NUM_THREADS];
	int ids[NUM_THREADS]; // tableau des identifiant
	for (int i = 0; i < NUM_THREADS; i++){
		ids[i] = i;
        // Second methode avec *id = malloc de qlq chose 
	    assert( pthread_create(&threads[i], NULL, thread, (void *) &ids[i]) == 0);
	}
	for (int i = 0; i < NUM_THREADS; i++)
		assert( pthread_join(threads[i], NULL) == 0);

	return EXIT_SUCCESS;
}
