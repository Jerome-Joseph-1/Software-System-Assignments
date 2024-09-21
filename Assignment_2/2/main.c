/*
============================================================================
Name : 2.c
Author : Jerome Joseph
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 21st September 2024
============================================================================
*/

// print_rlimits.c

#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {
    struct rlimit limit;
    int resources[] = {
        RLIMIT_CPU,
        RLIMIT_FSIZE,
        RLIMIT_DATA,
        RLIMIT_STACK,
        RLIMIT_CORE,
        RLIMIT_RSS,
        RLIMIT_NPROC,
        RLIMIT_NOFILE,
        RLIMIT_MEMLOCK,
        RLIMIT_AS,
        RLIMIT_LOCKS,
        RLIMIT_SIGPENDING,
        RLIMIT_MSGQUEUE,
        RLIMIT_NICE,
        RLIMIT_RTPRIO,
        RLIMIT_RTTIME,
    };
    const char *resource_names[] = {
        "RLIMIT_CPU",
        "RLIMIT_FSIZE",
        "RLIMIT_DATA",
        "RLIMIT_STACK",
        "RLIMIT_CORE",
        "RLIMIT_RSS",
        "RLIMIT_NPROC",
        "RLIMIT_NOFILE",
        "RLIMIT_MEMLOCK",
        "RLIMIT_AS",
        "RLIMIT_LOCKS",
        "RLIMIT_SIGPENDING",
        "RLIMIT_MSGQUEUE",
        "RLIMIT_NICE",
        "RLIMIT_RTPRIO",
        "RLIMIT_RTTIME",
    };

    int num_resources = sizeof(resources) / sizeof(resources[0]);

    for (int i = 0; i < num_resources; i++) {
        if (getrlimit(resources[i], &limit) == -1) {
            fprintf(stderr, "Error getting limit for %s: %s\n",
                    resource_names[i], strerror(errno));
            continue;
        }

        printf("%-20s ", resource_names[i]);

        if (limit.rlim_cur == RLIM_INFINITY)
            printf("Soft Limit: Unlimited\t\t");
        else
            printf("Soft Limit: %ld\t\t", (long)limit.rlim_cur);

        if (limit.rlim_max == RLIM_INFINITY)
            printf("Hard Limit: Unlimited\n");
        else
            printf("Hard Limit: %ld\n", (long)limit.rlim_max);
    }

    return 0;
}
/*

❯ ./run.sh                                                                                                                 ─╯
RLIMIT_CPU           Soft Limit: Unlimited              Hard Limit: Unlimited
RLIMIT_FSIZE         Soft Limit: Unlimited              Hard Limit: Unlimited
RLIMIT_DATA          Soft Limit: Unlimited              Hard Limit: Unlimited
RLIMIT_STACK         Soft Limit: 8388608                Hard Limit: Unlimited
RLIMIT_CORE          Soft Limit: Unlimited              Hard Limit: Unlimited
RLIMIT_RSS           Soft Limit: Unlimited              Hard Limit: Unlimited
RLIMIT_NPROC         Soft Limit: 125553         Hard Limit: 125553
RLIMIT_NOFILE        Soft Limit: 1024           Hard Limit: 524288
RLIMIT_MEMLOCK       Soft Limit: 8388608                Hard Limit: 8388608
RLIMIT_AS            Soft Limit: Unlimited              Hard Limit: Unlimited
RLIMIT_LOCKS         Soft Limit: Unlimited              Hard Limit: Unlimited
RLIMIT_SIGPENDING    Soft Limit: 125553         Hard Limit: 125553
RLIMIT_MSGQUEUE      Soft Limit: 819200         Hard Limit: 819200
RLIMIT_NICE          Soft Limit: 0              Hard Limit: 0
RLIMIT_RTPRIO        Soft Limit: 0              Hard Limit: 0
RLIMIT_RTTIME        Soft Limit: Unlimited              Hard Limit: Unlimited


*/