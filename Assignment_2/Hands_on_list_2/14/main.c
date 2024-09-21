/*
============================================================================
Name : 14.c
Author : Jerome Joseph
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.    
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello through the pipe!";
    char read_msg[100];

    pipe(fd);

    pid = fork();

    if (pid > 0) {
        close(fd[0]);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
    } else {
        close(fd[1]);
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Read from pipe: %s\n", read_msg);
        close(fd[0]);
    }

    return 0;
}

/*

❯ ./run.sh                                                                                                         ─╯
Read from pipe: Hello through the pipe!

*/