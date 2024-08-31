/*
============================================================================
Name : 4.c
Author : Jerome Joseph
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also.
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if(argc == 2) {
        char* filename = argv[1];

        int fd = open(filename, O_RDWR, S_IRWXU);

        if(-1 == fd) {
            perror("Error");
        } else {
            printf("File Opened Successfuly!\n");
            close(fd);
        }
    } else {
        printf("Usage: [executable] [filename]\n");
    }
}

/*
❯ ./main                                     ─╯
Usage: [executable] [filename]

❯ ./main file1                               ─╯
File Opened Successfuly!

❯ ./main file2                               ─╯
Error: No such file or directory

*/