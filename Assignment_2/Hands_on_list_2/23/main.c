/*
============================================================================
Name : 23.c
Author : Jerome Joseph
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 21st September 2024
============================================================================
*/
#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main() {
    struct rlimit rl;
    int pipe_fds[2];
    int pipe_size;

    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("Error getting RLIMIT_NOFILE");
        exit(EXIT_FAILURE);
    }

    printf("Maximum number of open files for this process:\n");
    printf("Soft limit: %ld\n", (long)rl.rlim_cur);
    printf("Hard limit: %ld\n\n", (long)rl.rlim_max);

    // Part 2: Create a pipe
    if (pipe(pipe_fds) == -1) {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }

    #ifdef F_GETPIPE_SZ
        pipe_size = fcntl(pipe_fds[0], F_GETPIPE_SZ);
        if (pipe_size == -1) {
            perror("Error getting pipe size with F_GETPIPE_SZ");
            close(pipe_fds[0]);
            close(pipe_fds[1]);
            exit(EXIT_FAILURE);
        }
        printf("Size of the pipe's circular buffer: %d bytes\n\n", pipe_size);
    #else
        printf("F_GETPIPE_SZ is not defined on this system. Cannot retrieve pipe buffer size.\n\n");
    #endif

    close(pipe_fds[0]);
    close(pipe_fds[1]);

    return 0;
}

/*
❯ ./run.sh                                                                                                  ─╯
Maximum number of open files for this process:
Soft limit: 1024
Hard limit: 524288

Size of the pipe's circular buffer: 65536 bytes

*/