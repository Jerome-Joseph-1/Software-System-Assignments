/*
============================================================================
Name : 31.c
Author : Jerome Joseph
Description : Write a program to create a semaphore and initialize value to the semaphore.
        a. create a binary semaphore
        b. create a counting semaphore
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    key_t key;
    int semid;
    union semun {
        int val;               
        struct semid_ds *buf;  
        unsigned short *array; 
        struct seminfo *__buf; 
    } sem_attr;

    key = ftok("/tmp", 'B');  
    if (key == -1) {
        perror("Error generating key using ftok");
        exit(EXIT_FAILURE);
    }
    
    semid = semget(key, 1, 0666 | IPC_CREAT);  
    if (semid == -1) {
        perror("Error creating semaphore using semget");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore created with ID: %d\n", semid);

    sem_attr.val = 1;
    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("Error initializing semaphore");
        exit(EXIT_FAILURE);
    }
    printf("Binary semaphore initialized to 1 (unlocked state).\n");

    return 0;
}

/*

❯ ./run.sh                                                                                                  ─╯
Semaphore created with ID: 0
Binary semaphore initialized to 1 (unlocked state).

*/