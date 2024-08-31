/*
============================================================================
Name : 29.c
Author : Jerome Joseph
Description : Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO,
SCHED_RR).
Date: 31st Aug, 2024.
============================================================================
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

void get_scheduling_policy(pid_t pid) {
    int policy = sched_getscheduler(pid);

    if (policy == -1) {
        perror("Error getting scheduling policy");
        exit(1);
    }

    switch (policy) {
        case SCHED_OTHER:
            printf("Current Scheduling Policy: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Current Scheduling Policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Current Scheduling Policy: SCHED_RR\n");
            break;
        default:
            printf("Unknown Scheduling Policy: %d\n", policy);
            break;
    }
}

void set_scheduling_policy(pid_t pid, int policy) {
    struct sched_param param;
    param.sched_priority = sched_get_priority_max(policy);

    if (sched_setscheduler(pid, policy, &param) == -1) {
        perror("Error setting scheduling policy");
        exit(1);
    }

    printf("Successfully changed scheduling policy to ");
    if (policy == SCHED_FIFO) {
        printf("SCHED_FIFO\n");
    } else if (policy == SCHED_RR) {
        printf("SCHED_RR\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <pid> <policy>\n", argv[0]);
        printf("Policy: 1 for SCHED_FIFO, 2 for SCHED_RR\n");
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    int policy_choice = atoi(argv[2]);
    int policy;

    switch (policy_choice) {
        case 1:
            policy = SCHED_FIFO;
            break;
        case 2:
            policy = SCHED_RR;
            break;
        default:
            printf("Invalid policy choice. Choose 1 for SCHED_FIFO, 2 for SCHED_RR.\n");
            return 1;
    }

    printf("Before change:\n");
    get_scheduling_policy(pid);

    set_scheduling_policy(pid, policy);

    printf("After change:\n");
    get_scheduling_policy(pid);

    return 0;
}


/*

❯ ./test                                                                                        ─╯
PID: 211643

❯ sudo ./main 211643 1                                                                                      ─╯
Before change:
Current Scheduling Policy: SCHED_OTHER
Successfully changed scheduling policy to SCHED_FIFO
After change:
Current Scheduling Policy: SCHED_FIFO

*/