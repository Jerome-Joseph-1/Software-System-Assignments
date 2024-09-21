/*
============================================================================
Name : 7.c
Author : Jerome Joseph
Description : Write a program to copy file1 into file2 ($cp file1 file2).
Date: 31st Aug, 2024.
============================================================================
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char** argv) {
    if(argc == 3) {
        char* src = argv[1];
        char* dest = argv[2];

        int src_fd = open(src, O_RDONLY);
        int dest_fd = open(dest, O_RDWR | O_CREAT | O_TRUNC, 0600);

        if(src_fd == -1 || dest_fd == -1) {
            printf("Error: failed opening files\n");
            perror("Error");
            return -1;
        }

        char buffer[1024];
        int bytes_read;

        while((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
            if(write(dest_fd, buffer, bytes_read) != bytes_read) {
                perror("Error");
                close(src_fd);
                close(dest_fd);
                return -1;
            }
        }

        if(bytes_read < 0) {
            perror("Error");
            return -1;
        }

        printf("Files copied successfully!\n");
        close(src_fd);
        close(dest_fd);         
    } else {
        printf("Usage: [executable] [src] [dest]\n");
    }

    return 0;
}

/*
❯ ./main                                     ─╯
Usage: [executable] [src] [dest]

❯ ./main file1 file2                         ─╯
Files copied successfully!

❯ cat file1                                  ─╯
TEMP FILE 
HAS CONTENT                                   ~/Doc/C/Assi/System Software/H/7  master ?6 ▓▒░

❯ cat file2                                  ─╯
TEMP FILE 
HAS CONTENT                                     ~/Doc/C/Assi/System Software/H/7  master ?6 ▓▒░

*/