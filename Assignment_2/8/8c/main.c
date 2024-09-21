/*
============================================================================
Name : 8c.c
Author : Jerome Joseph
Description :  Write a separate program using signal system call to catch the following signals
    c. SIGFPE
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigfpe_handler(int signum) {
    printf("Caught SIGFPE\n");
    exit(1);
}

int main() {
    signal(SIGFPE, sigfpe_handler);
    int x = 1 / 0;
    return 0;
}

/* OUTPUT

❯ ./run.sh                                                                                                                 ─╯
Caught SIGFPE

*/