/*
============================================================================
Name : 13.c
Author : Jerome Joseph
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date: 21st September 2024
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = atoi(argv[1]);
    printf("Sending SIGSTOP to process %d\n", pid);

    if (kill(pid, SIGSTOP) == -1) {
        perror("Failed to send SIGSTOP");
        exit(EXIT_FAILURE);
    }

    printf("SIGSTOP signal sent successfully.\n");
    
    return 0;
}

/*

❯ ./temp                                                                                                                   ─╯
Usage: ./temp <PID>
❯ ./temp 65875                                                                                                             ─╯
Sending SIGSTOP to process 65875
SIGSTOP signal sent successfully.

*/