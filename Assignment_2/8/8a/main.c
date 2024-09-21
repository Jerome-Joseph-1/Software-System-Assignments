/*
============================================================================
Name : 8a.c
Author : Jerome Joseph
Description : Write a separate program using signal system call to catch the following signals.
    a. SIGSEGV
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigsegv_handler(int signum) {
    printf("Caught SIGSEGV\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, sigsegv_handler);
    int *p = NULL;
    *p = 42;
    return 0;
}

/*

❯ ./run.sh                                                                                                                 ─╯
Caught SIGSEGV


*/