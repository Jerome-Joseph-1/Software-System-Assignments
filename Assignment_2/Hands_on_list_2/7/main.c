/*
============================================================================
Name : 7.c
Author : Jerome Joseph
Description : Write a simple program to print the created thread ids.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_function(void* arg) {
    pthread_t thread_id = pthread_self();   
    printf("Thread %d has ID: %lu\n", *((int*)arg), (unsigned long)thread_id);
    return NULL;
}

int main() {
    pthread_t threads[3];  
    int thread_args[3];    
    int result;

    
    for (int i = 0; i < 3; i++) {
        thread_args[i] = i + 1;  
        result = pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
        if (result != 0) {
            fprintf(stderr, "Error creating thread %d\n", i + 1);
            return 1;
        }
    }

    
    for (int i = 0; i < 3; i++) {
        result = pthread_join(threads[i], NULL);
        if (result != 0) {
            fprintf(stderr, "Error joining thread %d\n", i + 1);
            return 1;
        }
    }

    printf("All threads have finished executing.\n");

    return 0;
}

/*

❯ ./run.sh                                                                                                                 ─╯
Thread 1 has ID: 124337166223040
Thread 2 has ID: 124337155737280
Thread 3 has ID: 124337145251520
All threads have finished executing.

*/