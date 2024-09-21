/*
============================================================================
Name : 10a.c
Author : Jerome Joseph
Description : Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigsegv_handler(int signum) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigsegv_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGSEGV, &sa, NULL);

    int *p = NULL;
    *p = 42; 

    return 0;
}

/*

❯ ./run.sh                                                                                                                 ─╯
Caught SIGSEGV (Segmentation Fault)

*/