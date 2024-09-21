/*
============================================================================
Name : 26.c
Author : Jerome Joseph
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

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

    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("Error creating message queue using msgget");
        exit(EXIT_FAILURE);
    }
    
    message.msg_type = 1;  
    printf("Enter message: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);
    message.msg_text[strcspn(message.msg_text, "\n")] = '\0';  

    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("Error sending message");
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", message.msg_text);

    return 0;
}

/*

❯ ./run.sh                                                                                                  ─╯
Enter message: Hello Worl.d
Message sent: Hello Worl.d

❯ ipcs -q                                                                                                   ─╯
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0x422b0001 0          jerome     666        100          1           



*/