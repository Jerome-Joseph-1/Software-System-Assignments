/*
============================================================================
Name : 10.c
Author : Jerome Joseph
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
bytes (use lseek) and write again 10 bytes.
    a. check the return value of lseek
    b. open the file with od and check the empty spaces in between the data.
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv) {
    if(argc == 2) {
        char* filename = argv[1];

        int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644)   ;

        if(fd < 0) {
            perror("Error opening the file");
            return -1;
        }

        char buf1[] = "abcdefghij"; // 10 bytes
        char buf2[] = "mnbvcxzask"; // 10 bytes
        if(write(fd, buf1, 10) != 10) {
            perror("Error writing to file");
            close(fd);
            return -1;
        }

        int offset = lseek(fd, 10, SEEK_CUR);

        if(offset == -1) {
            perror("Error seeking");
            close(fd);
            return -1;
        }

        if(write(fd, buf2, 10) != 10) {
            perror("Error writing to file");
            close(fd);
            return -1;
        }
        
        close(fd);
    } else {
        printf("Usage: [executable] [filename]\n");
    }
}

/*

❯ ./main file1                                                                                                             ─╯

❯ cat file1                                                                                                                ─╯
abcdefghijmnbvcxzask%                                                                                                          ~/Documents/Code/Assignments/System Software/Hands_On_List_1/10  master ?9 ▓▒░                              ░▒▓ 06:42:09 ─╮

❯ od -x file1                                                                                                              ─╯
0000000 6261 6463 6665 6867 6a69 0000 0000 0000
0000020 0000 0000 6e6d 7662 7863 617a 6b73
0000036

*/