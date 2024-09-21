/*
============================================================================
Name : 6.c
Author : Jerome Joseph
Description : Write a simple program to create three threads.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_function(void* arg) {
    int thread_num = *((int*)arg);  
    printf("Hello from thread %d\n", thread_num);
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
Hello from thread 1
Hello from thread 3
Hello from thread 2
All threads have finished executing.

*/