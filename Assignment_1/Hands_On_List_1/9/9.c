/*
============================================================================
Name : 9.c
Author : Jerome Joseph
Description : Write a program to print the following information about a given file.
    a. inode
    b. number of hard links
    c. uid
    d. gid
    e. size
    f. block size
    g. number of blocks
    h. time of last access
    i. time of last modification
    j. time of last change
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char** argv) {
    if(argc == 2) {
        char* filename = argv[1];

        struct stat file_stat;

        int retval = stat(filename, &file_stat);

        if(retval == -1) {
            perror("Error");
            return -1;
        }

        printf("File: %s\n", filename);
        printf("Inode: %ld\n", file_stat.st_ino);
        printf("Number of hard links: %ld\n", file_stat.st_nlink);
        printf("UID: %d\n", file_stat.st_uid);
        printf("GID: %d\n", file_stat.st_gid);
        printf("Size: %ld bytes\n", file_stat.st_size);
        printf("Block size: %ld bytes\n", file_stat.st_blksize);
        printf("Number of blocks: %ld\n", file_stat.st_blocks);
        printf("Time of last access: %s", ctime(&file_stat.st_atime));
        printf("Time of last modification: %s", ctime(&file_stat.st_mtime));
        printf("Time of last change: %s", ctime(&file_stat.st_ctime));
    } else {
        printf("Usage: [executable] [filename]\n");
    }

    return 0;
}

/*

❯ ./main file1                               ─╯
File: file1
Inode: 13500924
Number of hard links: 1
UID: 1000
GID: 1000
Size: 65 bytes
Block size: 4096 bytes
Number of blocks: 8
Time of last access: Sat Aug 31 05:57:49 2024
Time of last modification: Sat Aug 31 05:57:56 2024
Time of last change: Sat Aug 31 05:57:56 2024

❯ ls -ali file1                              ─╯
13500924 -rw-r--r-- 1 jerome jerome 65 Aug 31 05:57 file1


*/