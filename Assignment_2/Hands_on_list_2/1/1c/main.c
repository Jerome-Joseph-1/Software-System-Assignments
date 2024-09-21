/*
============================================================================
Name : 1c.c
Author : Jerome Joseph
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
    c. ITIMER_PROF
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigprof(int sig) {
    printf("Received SIGPROF (ITIMER_PROF timer expired)\n");
}

int main() {
    struct itimerval timer;

    signal(SIGPROF, handle_sigprof);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("Error calling setitimer()");
        return 1;
    }

    while (1) {
        for (int i = 0; i < 10000; ++i);
        // System call - consume cpu cycles
        getpid();
    }

    return 0;
}

/*
❯ ./run.sh                         ─╯
Received SIGPROF (ITIMER_PROF timer expired)
*/