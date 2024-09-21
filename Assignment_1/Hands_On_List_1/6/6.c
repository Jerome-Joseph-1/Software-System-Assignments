/*
============================================================================
Name : 6.c
Author : Jerome Joseph
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 31st Aug, 2024.
============================================================================
*/

#include <unistd.h>
#include <fcntl.h>

int main() {
    char buffer[1000];

    int size_read = read(0, buffer, 1000);
    write(1,buffer, sizeof(size_read) + 1);

    return 0;
}

/*

❯ ./main                                     ─╯
ABCD
ABCD

*/