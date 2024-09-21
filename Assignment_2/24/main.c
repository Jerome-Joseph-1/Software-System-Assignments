/*
============================================================================
Name : 25.c
Author : Jerome Joseph
Description : Write a program to create a message queue and print the key and message queue id
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    key_t key;
    int msgid;

    key = ftok("/tmp", 'B');  

    if (key == -1) {
        perror("Error generating key using ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid == -1) {
        perror("Error creating message queue using msgget");
        exit(EXIT_FAILURE);
    }

    printf("Message queue key: %d\n", key);
    printf("Message queue ID: %d\n", msgid);

    return 0;
}


/*

❯ ./run.sh                                                                                                  ─╯
Message queue key: 1110114305
Message queue ID: 0


*/