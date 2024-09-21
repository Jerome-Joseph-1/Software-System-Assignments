/*
============================================================================
Name : 10b.c
Author : Jerome Joseph
Description : Write a separate program using sigaction system call to catch the following signals.
b. SIGINT
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum) {
    printf("Caught SIGINT (Interrupt from keyboard)\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C to trigger SIGINT...\n");
    pause();

    return 0;
}

/*

❯ ./run.sh                                                                                                                 ─╯
Press Ctrl+C to trigger SIGINT...
^C
Caught SIGINT (Interrupt from keyboard)

*/