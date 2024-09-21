/*
============================================================================
Name : 32.c
Author : Jerome Joseph
Description : Write a program to implement semaphore to protect any critical section.
        a. rewrite the ticket number creation program using semaphore
        b. protect shared memory from concurrent write access
        c. protect multiple pseudo resources ( may be two) using counting semaphore
        d. remove the created semaphore
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>

union semun {
    int val;                
    struct semid_ds *buf;   
    unsigned short *array;  
    struct seminfo *__buf;  
};

void semaphore_operation(int semid, int op) {
    struct sembuf sop;
    sop.sem_num = 0;   
    sop.sem_op = op;   
    sop.sem_flg = 0;
    if (semop(semid, &sop, 1) == -1) {
        perror("Semaphore operation failed");
        exit(EXIT_FAILURE);
    }
}

int main() {
    key_t key;
    int semid;
    union semun sem_attr;
    static int ticket_number = 0;  

    key = ftok("/tmp", 'T');
    if (key == -1) {
        perror("Error generating key using ftok");
        exit(EXIT_FAILURE);
    }

    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("Error creating semaphore using semget");
        exit(EXIT_FAILURE);
    }

    sem_attr.val = 1;
    if (semctl(semid, 0, SETVAL, sem_attr) == -1) {
        perror("Error initializing semaphore");
        exit(EXIT_FAILURE);
    }
    
    printf("Generating ticket numbers...\n");

    for (int i = 0; i < 5; i++) {
        semaphore_operation(semid, -1);  
        ticket_number++;
        printf("Ticket number: %d\n", ticket_number);
        semaphore_operation(semid, 1);   
    }

    return 0;
}
