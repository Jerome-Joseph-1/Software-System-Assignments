/*
============================================================================
Name : 28.c
Author : Jerome Joseph
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
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
    struct msqid_ds buf;

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

    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("Error getting message queue info");
        exit(EXIT_FAILURE);
    }

    printf("Current permissions: %o\n", buf.msg_perm.mode & 0777);

    buf.msg_perm.mode = (buf.msg_perm.mode & ~0777) | 0644;  

    if (msgctl(msgid, IPC_SET, &buf) == -1) {
        perror("Error setting message queue permissions");
        exit(EXIT_FAILURE);
    }

    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("Error retrieving updated message queue info");
        exit(EXIT_FAILURE);
    }
    
    printf("Updated permissions: %o\n", buf.msg_perm.mode & 0777);

    return 0;
}

/*

❯ ./run.sh                                                                                                  ─╯
Current permissions: 666
Updated permissions: 644

*/