/*
============================================================================
Name : 3.c
Author : Jerome Joseph
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main() {
    struct rlimit limit;
    int result;

    result = getrlimit(RLIMIT_NOFILE, &limit);
    if (result == -1) {
        fprintf(stderr, "Error getting RLIMIT_NOFILE: %s\n", strerror(errno));
        return 1;
    }

    printf("Current RLIMIT_NOFILE:\n");
    printf("Soft Limit: %ld\n", (long)limit.rlim_cur);
    printf("Hard Limit: %ld\n", (long)limit.rlim_max);

    limit.rlim_cur = limit.rlim_cur / 2;

    if (limit.rlim_cur > limit.rlim_max) {
        limit.rlim_cur = limit.rlim_max;
    }

    result = setrlimit(RLIMIT_NOFILE, &limit);
    if (result == -1) {
        fprintf(stderr, "Error setting RLIMIT_NOFILE: %s\n", strerror(errno));
        return 1;
    }

    printf("\nNew RLIMIT_NOFILE set successfully.\n");

    result = getrlimit(RLIMIT_NOFILE, &limit);
    if (result == -1) {
        fprintf(stderr, "Error getting RLIMIT_NOFILE: %s\n", strerror(errno));
        return 1;
    }

    printf("Updated RLIMIT_NOFILE:\n");
    printf("Soft Limit: %ld\n", (long)limit.rlim_cur);
    printf("Hard Limit: %ld\n", (long)limit.rlim_max);

    return 0;
}


/*
❯ ./run.sh                                                                                                                 ─╯
Current RLIMIT_NOFILE:
Soft Limit: 1024
Hard Limit: 524288

New RLIMIT_NOFILE set successfully.
Updated RLIMIT_NOFILE:
Soft Limit: 512
Hard Limit: 524288

*/