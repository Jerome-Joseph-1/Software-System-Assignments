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

#include "train_struct.c"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>        
#include <string.h>
#include <errno.h>

#define SHM_SIZE 1024  
#define PSEUDO_RESOURCES 2  

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


void create_binary_semaphore(int *semid) {
    key_t key = ftok("/tmp", 'T');
    if (key == -1) {
        perror("Error generating key using ftok");
        exit(EXIT_FAILURE);
    }
    *semid = semget(key, 1, 0666 | IPC_CREAT);
    if (*semid == -1) {
        perror("Error creating semaphore using semget");
        exit(EXIT_FAILURE);
    }
    union semun sem_attr;
    sem_attr.val = 1;  
    if (semctl(*semid, 0, SETVAL, sem_attr) == -1) {
        perror("Error initializing semaphore");
        exit(EXIT_FAILURE);
    }
    printf("Binary semaphore created and initialized.\n");
}


void ticket_number_creation(int semid) {
    static int ticket_number = 0;
    key_t shm_key = ftok("/tmp", 'S');
    int shmid = shmget(shm_key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("Error creating shared memory");
        exit(EXIT_FAILURE);
    }
    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("Error attaching shared memory");
        exit(EXIT_FAILURE);
    }

    semaphore_operation(semid, -1);  
    ticket_number++;
    sprintf(shared_memory, "Ticket number: %d", ticket_number);
    printf("%s\n", shared_memory);
    semaphore_operation(semid, 1);   

    if (shmdt(shared_memory) == -1) {
        perror("Error detaching shared memory");
        exit(EXIT_FAILURE);
    }
}


void protect_pseudo_resources(int *counting_semid) {
    key_t count_key = ftok("/tmp", 'C');
    *counting_semid = semget(count_key, 1, 0666 | IPC_CREAT);
    if (*counting_semid == -1) {
        perror("Error creating counting semaphore");
        exit(EXIT_FAILURE);
    }
    union semun sem_attr;
    sem_attr.val = PSEUDO_RESOURCES;  
    if (semctl(*counting_semid, 0, SETVAL, sem_attr) == -1) {
        perror("Error initializing counting semaphore");
        exit(EXIT_FAILURE);
    }
    printf("Counting semaphore initialized to %d resources.\n", PSEUDO_RESOURCES);

    
    printf("Acquiring resource...\n");
    semaphore_operation(*counting_semid, -1);  
    printf("Resource acquired.\n");
    printf("Releasing resource...\n");
    semaphore_operation(*counting_semid, 1);   
    printf("Resource released.\n");
}


void remove_semaphore(int semid) {
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("Error removing semaphore");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore removed successfully.\n");
}

int main() {
    int binary_semid, counting_semid;

    
    create_binary_semaphore(&binary_semid);

    
    ticket_number_creation(binary_semid);

    
    protect_pseudo_resources(&counting_semid);

    
    remove_semaphore(binary_semid);
    remove_semaphore(counting_semid);

    return 0;
}


/*

❯ ./run.sh                                                                                                  ─╯
Binary semaphore created and initialized.
Ticket number: 1
Counting semaphore initialized to 2 resources.
Acquiring resource...
Resource acquired.
Releasing resource...
Resource released.
Semaphore removed successfully.
Semaphore removed successfully.

*/