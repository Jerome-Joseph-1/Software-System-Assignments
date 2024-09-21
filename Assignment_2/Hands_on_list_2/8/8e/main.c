/*
============================================================================
Name : 8e.c
Author : Jerome Joseph
Description :  Write a separate program using signal system call to catch the following signals
    e. SIGALRM (use setitimer system call)
Date: 21st September 2024
============================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void sigalrm_handler(int signum) {
    printf("Caught SIGALRM\n");
}

int main() {
    struct itimerval timer;
    signal(SIGALRM, sigalrm_handler);
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
    pause();
    return 0;
}


/* OUTPUT

❯ ./run.sh                                                                                                                 ─╯
Caught SIGALRM

*/