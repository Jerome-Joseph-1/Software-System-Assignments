/*
============================================================================
Name : 25.c
Author : Jerome Joseph
Description : Write a program to create three child processes. The parent should wait for a particular child (use
waitpid system call).
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid[3];
    int i;

    for (i = 0; i < 3; i++) {
        pid[i] = fork();

        if (pid[i] < 0) {
            perror("fork");
            exit(-1);
        }

        if (pid[i] == 0) {
            printf("Child %d (PID: %d) is running.\n", i, getpid());
            sleep(10 + i); 
            printf("Child %d (PID: %d) is exiting.\n", i, getpid());
            return 0;
        }
    }

    printf("Parent process (PID: %d) is waiting for a specific child.\n", getpid());

    int status;
    pid_t target_pid = pid[1]; // We will wait for the second child process
    pid_t waited_pid = waitpid(target_pid, &status, 0);

    if (waited_pid < 0) {
        perror("waitpid");
        exit(1);
    }

    if (WIFEXITED(status)) {
        printf("Parent process (PID: %d) waited for child %d (PID: %d) with exit status %d.\n",
               getpid(), 1, waited_pid, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("Child %d (PID: %d) terminated by signal %d.\n",
               1, waited_pid, WTERMSIG(status));
    }

    printf("Parent process (PID: %d) will terminate now.\n", getpid());

    return 0;
}

/*

❯ ./main                                                                                        ─╯
Child 0 (PID: 205521) is running.
Parent process (PID: 205520) is waiting for a specific child.
Child 1 (PID: 205522) is running.
Child 2 (PID: 205523) is running.
Child 0 (PID: 205521) is exiting.
Child 1 (PID: 205522) is exiting.
Parent process (PID: 205520) waited for child 1 (PID: 205522) with exit status 0.
Parent process (PID: 205520) will terminate now.


*/