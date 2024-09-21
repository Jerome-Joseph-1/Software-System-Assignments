/*
============================================================================
Name : 5.c
Author : Jerome Joseph
Description : Write a program to print the system limitation of
    a. maximum length of the arguments to the exec family of functions.
    b. maximum number of simultaneous process per user id.
    c. number of clock ticks (jiffy) per second.
    d. maximum number of open files
    e. size of a page
    f. total number of pages in the physical memory
    g. number of currently available pages in the physical memory.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    long arg_max, child_max, clk_tck, open_max, page_size, phys_pages, avail_pages;

    // a. Maximum length of the arguments to the exec family of functions
    arg_max = sysconf(_SC_ARG_MAX);
    if (arg_max == -1) {
        perror("sysconf(_SC_ARG_MAX)");
    } else {
        printf("Maximum length of arguments to exec functions: %ld bytes\n", arg_max);
    }

    // b. Maximum number of simultaneous processes per user id
    child_max = sysconf(_SC_CHILD_MAX);
    if (child_max == -1) {
        perror("sysconf(_SC_CHILD_MAX)");
    } else {
        printf("Maximum number of simultaneous processes per user id: %ld\n", child_max);
    }

    // c. Number of clock ticks (jiffy) per second
    clk_tck = sysconf(_SC_CLK_TCK);
    if (clk_tck == -1) {
        perror("sysconf(_SC_CLK_TCK)");
    } else {
        printf("Number of clock ticks per second: %ld\n", clk_tck);
    }

    // d. Maximum number of open files
    open_max = sysconf(_SC_OPEN_MAX);
    if (open_max == -1) {
        perror("sysconf(_SC_OPEN_MAX)");
    } else {
        printf("Maximum number of open files: %ld\n", open_max);
    }

    // e. Size of a page (in bytes)
    page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) {
        perror("sysconf(_SC_PAGESIZE)");
    } else {
        printf("Size of a memory page: %ld bytes\n", page_size);
    }

    // f. Total number of pages in the physical memory
    phys_pages = sysconf(_SC_PHYS_PAGES);
    if (phys_pages == -1) {
        perror("sysconf(_SC_PHYS_PAGES)");
    } else {
        printf("Total number of pages in physical memory: %ld\n", phys_pages);
    }

    // g. Number of currently available pages in the physical memory
    avail_pages = sysconf(_SC_AVPHYS_PAGES);
    if (avail_pages == -1) {
        perror("sysconf(_SC_AVPHYS_PAGES)");
    } else {
        printf("Number of currently available pages in physical memory: %ld\n", avail_pages);
    }

    return 0;
}

/*

❯ ./run.sh                                                                                                                 ─╯
Maximum length of arguments to exec functions: 2097152 bytes
Maximum number of simultaneous processes per user id: 125553
Number of clock ticks per second: 100
Maximum number of open files: 1024
Size of a memory page: 4096 bytes
Total number of pages in physical memory: 8042273
Number of currently available pages in physical memory: 5631635

*/