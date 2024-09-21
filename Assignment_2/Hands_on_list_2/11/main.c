/*
============================================================================
Name : 11.c
Author : Jerome Joseph
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
use sigaction system call.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum) {
    printf("SIGINT signal ignored. Press Ctrl+C again after 5 seconds to terminate the program.\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT is now ignored. Press Ctrl+C...\n");

    
    pause();    

    
    sa.sa_handler = SIG_DFL;  
    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT signal reset to default behavior. Press Ctrl+C again to terminate the program.\n");
    
    pause();  

    return 0;
}

/*

❯ ./run.sh                                                                                                                 ─╯
SIGINT is now ignored. Press Ctrl+C...
^C
SIGINT signal ignored. 
SIGINT signal reset to default behavior. Press Ctrl+C again to terminate the program.
^C

*/