/*
============================================================================
Name : 10c.c
Author : Jerome Joseph
Description : Write a separate program using sigaction system call to catch the following signals.
c. SIGFPE
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigfpe_handler(int signum) {
    printf("Caught SIGFPE (Floating-Point Exception)\n");
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigfpe_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGFPE, &sa, NULL);

    int x = 1 / 0;  
    
    return 0;
}


/*

❯ ./run.sh                                                                                                                 ─╯
Caught SIGFPE (Floating-Point Exception)

*/