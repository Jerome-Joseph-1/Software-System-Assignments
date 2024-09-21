/*
============================================================================
Name : 15.c
Author : Jerome Joseph
Description : Write a simple program to send some data from parent to the child process.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char message[] = "Message from parent to child";
    char buffer[100];

    pipe(fd);
    pid = fork();

    if (pid > 0) {
        close(fd[0]); 
        write(fd[1], message, strlen(message) + 1);  
        close(fd[1]);  
    } else if (pid == 0) {
        close(fd[1]);  
        read(fd[0], buffer, sizeof(buffer));  
        printf("Child received: %s\n", buffer);
        close(fd[0]);  
    }

    return 0;
}

/*

❯ ./run.sh                                                                                                         ─╯
Child received: Message from parent to child


*/