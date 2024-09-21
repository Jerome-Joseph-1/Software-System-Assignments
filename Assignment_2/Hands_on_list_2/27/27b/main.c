/*
============================================================================
Name : 27a.c
Author : Jerome Joseph
Description : Write a program to receive messages from the message queue.
        a. with 0 as a flag
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    
    key = ftok("/tmp", 'B');
    if (key == -1) {
        perror("Error generating key using ftok");
        exit(EXIT_FAILURE);
    }

    
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Error getting message queue ID");
        exit(EXIT_FAILURE);
    }

    
    printf("Attempting to receive a message (non-blocking)...\n");
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            printf("No message available at the moment.\n");
        } else {
            perror("Error receiving message");
        }
        exit(EXIT_FAILURE);
    }

    
    printf("Received message: %s\n", message.msg_text);

    return 0;
}

/*

❯ ./run.sh                                                                                                  ─╯
Attempting to receive a message (non-blocking)...
Received message: JAKSBNCKJASNCKJ NKAJCNK SJN 

*/