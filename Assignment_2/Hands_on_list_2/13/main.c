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
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum) {
    printf("Caught signal %d\n", signum);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    sigaction(SIGSTOP, &sa, NULL);

    printf("Waiting for signals... (PID: %d)\n", getpid());

    while (1) {
        pause();
    }

    return 0;
}

/*

❯ ./main                                                                                                           ─╯
Waiting for signals... (PID: 65875)
---- run ./temp ------
zsh: suspended (signal)  ./main

*/