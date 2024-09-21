/*
============================================================================
Name : 29.c
Author : Jerome Joseph
Description : Write a program to remove the message queue.
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
    
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("Error getting message queue ID");
        exit(EXIT_FAILURE);
    }
    
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("Error removing message queue");
        exit(EXIT_FAILURE);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}

/*

❯ ipcs -q                                                                                                   ─╯
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x422b0001 2          jerome     666        100          1           

❯ ./run.sh                                                                                                  ─╯
Message queue removed successfully.

❯ ipcs -q                                                                                                   ─╯
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    


*/