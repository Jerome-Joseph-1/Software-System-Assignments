/*
============================================================================
Name : 25.c
Author : Jerome Joseph
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
        a. access permission
        b. uid, gid
        c. time of last message sent and received
        d. time of last change in the message queue
        d. size of the queue
        f. number of messages in the queue
        g. maximum number of bytes allowed
        h. pid of the msgsnd and msgrcv
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>
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

    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("Error getting message queue ID using msgget");
        exit(EXIT_FAILURE);
    }

    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("Error getting message queue info using msgctl");
        exit(EXIT_FAILURE);
    }


    printf("Access permissions: %o\n", buf.msg_perm.mode & 0777);

    printf("UID: %d\n", buf.msg_perm.uid);
    printf("GID: %d\n", buf.msg_perm.gid);

    printf("Time of last message sent: %s", ctime(&buf.msg_stime));

    printf("Time of last message received: %s", ctime(&buf.msg_rtime));

    printf("Time of last change: %s", ctime(&buf.msg_ctime));

    printf("Current size of the queue (bytes): %lu\n", buf.__msg_cbytes);

    printf("Number of messages in the queue: %lu\n", buf.msg_qnum);

    printf("Maximum number of bytes allowed in the queue: %lu\n", buf.msg_qbytes);

    printf("PID of last msgsnd: %d\n", buf.msg_lspid);
    printf("PID of last msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}

/*

❯ ./run.sh                                                                                                  ─╯
Access permissions: 666
UID: 1000
GID: 1000
Time of last message sent: Thu Jan  1 05:30:00 1970
Time of last message received: Thu Jan  1 05:30:00 1970
Time of last change: Sat Sep 21 16:59:14 2024
Current size of the queue (bytes): 0
Number of messages in the queue: 0
Maximum number of bytes allowed in the queue: 16384
PID of last msgsnd: 0
PID of last msgrcv: 0

*/