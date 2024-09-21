/*
============================================================================
Name : 20.c
Author : Jerome Joseph
Description : Write a program to find out time taken to execute getpid system call. Use time stamp counter
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = getpid();
    printf("PID: %d\n", pid);
    while(1);
}


/*

❯ ./run_loop                                                                                    ─╯
PID: 198228

❯ ps -o pid,ni,comm -p 198228                                                                   ─╯
    PID  NI COMMAND
 198228   0 run_loop

❯ sudo nice -n -10 ./run_loop                                                                   ─╯
PID: 198625

❯ ps -o pid,ni,comm -p 198625                                                                   ─╯
    PID  NI COMMAND
 198625 -10 run_loop

❯ sudo renice -n -5 -p 198625                                                                   ─╯
198625 (process ID) old priority -10, new priority -5

❯ ps -o pid,ni,comm -p 198625                                                                   ─╯
    PID  NI COMMAND
 198625  -5 run_loop

*/