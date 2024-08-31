/*
============================================================================
Name : 8.c
Author : Jerome Joseph
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read.
Close the file when end of file is reached.
Date: 31st Aug, 2024.
============================================================================
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if(argc == 2) {
        char* filename = argv[1];

        int fd = open(filename, O_RDONLY);

        if(fd < 0) {
            perror("Error");
            return -1;
        } 
        int buffer_size = 1024;
        char buffer[buffer_size];

        int bytes_read, start = 0;

        while((bytes_read = read(fd, buffer, buffer_size)) > 0) {
            for (int i = 0; i < bytes_read; i++) {
                if (buffer[i] == '\n') {
                    write(1, buffer + start, i - start + 1);
                    start = i + 1;
                }
            }
            if (start < bytes_read) {
                write(1, buffer + start, bytes_read - start);
            }
            start = 0;
        }

        close(fd);
        if (bytes_read < 0) {
            perror("Error reading file");
            return -1;
        }
    } else {
        printf("Usage: [executable] [filename]\n");
    }
}

/*

❯ ./main                                     ─╯
Usage: [executable] [filename]

❯ ./main file1                               ─╯
This is a file 
This file has content 
Just some random text


*/