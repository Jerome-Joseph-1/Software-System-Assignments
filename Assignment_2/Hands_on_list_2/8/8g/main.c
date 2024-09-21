/*
============================================================================
Name : 8g.c
Author : Jerome Joseph
Description :  Write a separate program using signal system call to catch the following signals
    g. SIGPROF (use setitimer system call)
Date: 21st September 2024
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void sigprof_handler(int signum) {
    printf("Caught SIGPROF\n");
    exit(1);
}

int main() {
    struct itimerval timer;
    signal(SIGPROF, sigprof_handler);
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_PROF, &timer, NULL);
    while(1);
    return 0;
}


/* OUTPUT

❯ ./run.sh                                                                                                                 ─╯
Caught SIGPROF

*/