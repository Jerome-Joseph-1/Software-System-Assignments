/*
============================================================================
Name : 8f.c
Author : Jerome Joseph
Description :  Write a separate program using signal system call to catch the following signals
    f. SIGVTALRM (use setitimer system call)
Date: 21st September 2024
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void sigvtalrm_handler(int signum) {
    printf("Caught SIGVTALRM\n");
    exit(1);
}

int main() {
    struct itimerval timer;
    signal(SIGVTALRM, sigvtalrm_handler);
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    while(1);
    return 0;
}

/* OUTPUT

❯ ./run.sh                                                                                                                 ─╯
Caught SIGVTALRM

*/