/*
============================================================================
Name : 9.c
Author : Jerome Joseph
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ignore_sigint(int signum) {
    printf("SIGINT ignored. Press Ctrl+C again after 5 seconds to exit.\n");
}

int main() {
    signal(SIGINT, ignore_sigint);
    printf("SIGINT signal is now ignored. Press Ctrl+C...\n");
    
    pause();

    signal(SIGINT, SIG_DFL);
    printf("SIGINT signal reset to default. Press Ctrl+C again to terminate.\n");

    pause(); 

    return 0;
}

/*

❯ ./run.sh                                                                                                                 ─╯
SIGINT signal is now ignored. Press Ctrl+C...
^C 
SIGINT ignored. Press Ctrl+C again to exit.
SIGINT signal reset to default. Press Ctrl+C again to terminate.
^C

*/