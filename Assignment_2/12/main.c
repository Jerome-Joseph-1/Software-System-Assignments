/*
============================================================================
Name : 
Author : Jerome Joseph
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
the parent process from the child process.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Child process: sending SIGKILL to parent process with PID %d\n", getppid());
        kill(getppid(), SIGKILL);

        sleep(5);  
        printf("Child process: parent has been killed. N    ow adopted by init (or systemd) with new parent PID %d\n", getppid());

    } else {
        printf("Parent process: PID %d\n", getpid());
        sleep(10);  
    }

    return 0;
}

/*

❯ ./run.sh                                                                                                                 ─╯
Parent process: PID 65172
Child process: sending SIGKILL to parent process with PID 65172
./run.sh: line 6: 65172 Killed                  ./main
Child process: parent has been killed. Now adopted by init (or systemd) with new parent PID 841                          ─╯

*/