/*
============================================================================
Name : 23.c
Author : Jerome Joseph
Description : Write a program to create a Zombie state of the running program.
Date: 31st Aug, 2024.
============================================================================
*/      

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Child process (PID: %d) is running.\n", getpid());
        printf("Child process Ended.\n");
        exit(0);
    } else {
        printf("Parent process (PID: %d) will sleep to create a zombie (child process).\n", getpid());
        sleep(5);
        printf("Parent process (PID: %d) is now exiting.\n", getpid());
    }

    return 0;
}

/*

❯ ./main                                                                                        ─╯
Parent process (PID: 203254) will sleep to create a zombie (child process).
Child process (PID: 203255) is running.
Child process Ended.
Parent process (PID: 203254) is now exiting.


*/