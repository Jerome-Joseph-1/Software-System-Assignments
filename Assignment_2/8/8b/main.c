/*
============================================================================
Name : 8b.c
Author : Jerome Joseph
Description : Write a separate program using signal system call to catch the following signals
    b. SIGINT
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>

void sigint_handler(int signum) {
    printf( "Caught SIGINT\n");
}

int main() {
    signal(SIGINT, sigint_handler);
    printf("Press Ctrl+C...\n");
    while (1);
    return 0;
}

/* OUTPUT

❯ ./run.sh                                                                                                                 ─╯
Press Ctrl+C...
^CCaught SIGINT

*/