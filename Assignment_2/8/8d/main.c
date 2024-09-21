/*
============================================================================
Name : 8d.c
Author : Jerome Joseph
Description :  Write a separate program using signal system call to catch the following signals
    d. SIGALRM (use alarm system call)
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigalrm_handler(int signum) {
    printf("Caught SIGALRM\n");
}

int main() {
    signal(SIGALRM, sigalrm_handler);
    alarm(3);
    pause();
    return 0;
}

/* OUTPUT

❯ ./run.sh                                                                                                                 ─╯
Caught SIGALRM

*/