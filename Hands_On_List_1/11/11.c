/*
============================================================================
Name : 11.c
Author : Jerome Joseph
Description : Write a program to open a file, duplicate the file descriptor and append the file with both the
descriptors and check whether the file is updated properly or not.
    a. use dup
    b. use dup2
    c. use fcntl
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv) {
    if(argc == 2) {

        int fd, fd_dup1, fd_dup2, fd_fcntl;
    char *filename = argv[1];
        char *data1 = "Appended using original fd\n";
        char *data2 = "Appended using dup\n";
        char *data3 = "Appended using dup2\n";
        char *data4 = "Appended using fcntl\n";

        fd = open(filename, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            perror("Error opening file");
            return -1;
        }

        fd_dup1 = dup(fd);
        if (fd_dup1 < 0) {
            perror("Error duplicating fd with dup");
            close(fd);
            return -1;
        }

        fd_dup2 = dup2(fd, fd_dup1 + 1);
        if (fd_dup2 < 0) {
            perror("Error duplicating fd with dup2");
            close(fd);
            close(fd_dup1);
            return -1;
        }

        fd_fcntl = fcntl(fd, F_DUPFD, fd_dup2 + 1);  
        if (fd_fcntl < 0) {
            perror("Error duplicating fd with fcntl");
            close(fd);
            close(fd_dup1);
            close(fd_dup2);
            return -1;
        }

        if (write(fd, data1, strlen(data1)) != strlen(data1)) {
            perror("Error writing with original fd");
        }

        if (write(fd_dup1, data2, strlen(data2)) != strlen(data2)) {
            perror("Error writing with dup fd");
        }

        if (write(fd_dup2, data3, strlen(data3)) != strlen(data3)) {
            perror("Error writing with dup2 fd");
        }

        if (write(fd_fcntl, data4, strlen(data4)) != strlen(data4)) {
            perror("Error writing with fcntl fd");
        }

        close(fd);
        close(fd_dup1);
        close(fd_dup2);
        close(fd_fcntl);

        printf("Data written to: %s\n", filename);
    } else {
        printf("Usage: [executable] [filename]\n");
    }


    return 0;
}


/*
❯ ./main                                                                                        ─╯
Usage: [executable] [filename]

❯ ./main file1                                                                                  ─╯
Data written to: file1

❯ cat file1                                                                                     ─╯
Appended using original fd
Appended using dup
Appended using dup2
Appended using fcntl

*/