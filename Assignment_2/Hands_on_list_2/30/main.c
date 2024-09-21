/*
============================================================================
Name : 30.c
Author : Jerome Joseph
Description : Write a program to create a shared memory.
    a. write some data to the shared memory
    b. attach with O_RDONLY and check whether you are able to overwrite.
    c. detach the shared memory
    d. remove the shared memory
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>

#define SHM_SIZE 1024  

int main() {
    key_t key;
    int shmid;
    char *shmaddr;

    key = ftok("/tmp", 'R');  
    if (key == -1) {
        perror("Error generating key using ftok");
        exit(EXIT_FAILURE);
    }
    
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("Error creating shared memory using shmget");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory created with ID: %d\n", shmid);
    
    shmaddr = (char *)shmat(shmid, NULL, 0);  
    if (shmaddr == (char *)-1) {
        perror("Error attaching shared memory");
        exit(EXIT_FAILURE);
    }
    
    strcpy(shmaddr, "Hello, Shared Memory!");
    printf("Data written to shared memory: %s\n", shmaddr);
    
    char *shmaddr_ro = (char *)shmat(shmid, NULL, SHM_RDONLY);  
    if (shmaddr_ro == (char *)-1) {
        perror("Error attaching shared memory in read-only mode");
        exit(EXIT_FAILURE);
    }
    printf("Data in read-only shared memory: %s\n", shmaddr_ro);

    printf("Attempting to overwrite data in read-only mode...\n");
    strcpy(shmaddr_ro, "Overwriting...");  
    printf("Overwrite attempt in read-only mode successful (this should not happen).\n");
    
    if (shmdt(shmaddr) == -1) {
        perror("Error detaching shared memory (read-write)");
        exit(EXIT_FAILURE);
    }
    if (shmdt(shmaddr_ro) == -1) {
        perror("Error detaching shared memory (read-only)");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory detached.\n");
        
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Error removing shared memory");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory removed successfully.\n");

    return 0;
}

/*

❯ ./run.sh                                                                                                  ─╯
Shared memory created with ID: 31
Data written to shared memory: Hello, Shared Memory!
Data in read-only shared memory: Hello, Shared Memory!
Attempting to overwrite data in read-only mode...
./run.sh: line 6: 20891 Segmentation fault      (core dumped) ./main
====================================================================
❯ ./run.sh                                                                                                  ─╯
Shared memory created with ID: 31
Data written to shared memory: Hello, Shared Memory!
Data in read-only shared memory: Hello, Shared Memory!
Shared memory detached.
Shared memory removed successfully.

*/