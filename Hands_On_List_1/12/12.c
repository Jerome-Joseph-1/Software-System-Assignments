/*
============================================================================
Name : 12.c
Author : Jerome Joseph
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date: 31st Aug, 2024.
============================================================================
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if(argc == 2) {
        char* filename = argv[1]; 

        int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);

        if(fd < 0) {
            perror("Error opening file");
            return -1;
        }

        int flags = fcntl(fd, F_GETFL);

        switch(flags & O_ACCMODE) {
            case O_RDONLY: 
                printf("Opened with Read Only\n");
                break;
            case O_WRONLY: 
                printf("Opened with Write Only\n");
                break;
            case O_RDWR:
                printf("Opened with Read & Write\n");
                break;
        }

        close(fd);  
    } else {
        printf("Usage: [exectuable] [filename]\n");
    }
}

/*

❯ ./main                                                                                        ─╯
Usage: [exectuable] [filename]

❯ ./main file1                                                                                  ─╯
Opened with Read & Write


*/