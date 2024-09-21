/*
============================================================================
Name : 28.c
Author : Jerome Joseph
Description : Write a program to get maximum and minimum real time priority.
Date: 31st Aug, 2024.
============================================================================
*/  

#include <stdio.h>
#include <sched.h>

int main() {
    int max_priority, min_priority;

    max_priority = sched_get_priority_max(SCHED_FIFO);
    min_priority = sched_get_priority_min(SCHED_FIFO);

    if (max_priority == -1 || min_priority == -1) {
        perror("Error getting real-time priorities");
        return 1;
    }

    printf("SCHED_FIFO: Max priority = %d, Min priority = %d\n", max_priority, min_priority);

    max_priority = sched_get_priority_max(SCHED_RR);
    min_priority = sched_get_priority_min(SCHED_RR);

    if (max_priority == -1 || min_priority == -1) {
        perror("Error getting real-time priorities");
        return 1;
    }

    printf("SCHED_RR: Max priority = %d, Min priority = %d\n", max_priority, min_priority);

    return 0;
}


/*
❯ ./main                                                                                        ─╯
SCHED_FIFO: Max priority = 99, Min priority = 1
SCHED_RR: Max priority = 99, Min priority = 1

*/