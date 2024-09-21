/*
============================================================================
Name : 1b.c
Author : Jerome Joseph
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
    b. ITIMER_VIRTUAL
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_sigvtalrm(int sig) {
    printf("Received SIGVTALRM (ITIMER_VIRTUAL timer expired)\n");
}

int main() {
    struct itimerval timer;

    signal(SIGVTALRM, handle_sigvtalrm);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("Error calling setitimer()");
        return 1;
    }

    while (1) {
        for (int i = 0; i < 1000000; ++i);
    }

    return 0;
}

/*

❯ ./run.sh                           ─╯
Received SIGVTALRM (ITIMER_VIRTUAL timer expired)

*/