/*
============================================================================
Name : 4.c
Author : Jerome Joseph
Description : Write a program to measure how much time is taken to execute 100 getppid ( )
system call. Use time stamp counter.    
Date: 21st September 2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <x86intrin.h> 

int main() {
    unsigned long long start, end;
    pid_t ppid;
    int i;

    start = __rdtsc();
    for (i = 0; i < 100; i++) {
        ppid = getppid();
    }
    end = __rdtsc();

    printf("Time taken for 100 getppid() calls: %llu cycles\n", (end - start));

    return 0;
}

/*

❯ ./run.sh                                                                                                                 ─╯
Time taken for 100 getppid() calls: 40698 cycles

*/