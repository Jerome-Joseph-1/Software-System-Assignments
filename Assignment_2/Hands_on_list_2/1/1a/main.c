/*
============================================================================
Name : 1a.c
Author : Jerome Joseph
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
    a. ITIMER_REAL
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigalrm(int sig) {
    printf("Received SIGALRM (ITIMER_REAL timer expired)\n");
}

int main() {
    struct itimerval timer;

    signal(SIGALRM, handle_sigalrm);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Error calling setitimer()");
        return 1;
    }

    while (1) {
        sleep(1);
    }

    return 0;
}


/*
OUTPUT:
==========================================
❯ ./run.sh                           ─╯
Received SIGALRM (ITIMER_REAL timer expired)
*/