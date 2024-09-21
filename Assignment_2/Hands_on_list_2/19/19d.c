/*
============================================================================
Name : 19.c
Author : Jerome Joseph
Description : Create a FIFO file by
        d. mkfifo library function
Date: 21st September 2024
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

int main() {
    const char *fifo_path = "myfifo_mkfifo";
    int result;

    result = mkfifo(fifo_path, 0666);
    if (result == -1) {
        perror("Error creating FIFO with mkfifo");
        return errno;
    }

    printf("FIFO '%s' created using mkfifo library function.\n", fifo_path);
    return 0;
}

/*

❯ gcc -o main 19d.c && ./main                                                                   ─╯
FIFO 'myfifo_mkfifo' created using mkfifo library function.

❯ ls -al myfifo_mkfifo myfifo_mknod                                                             ─╯
prw-r--r-- 1 jerome jerome 0 Sep 21 16:11 myfifo_mkfifo
prw-r--r-- 1 jerome jerome 0 Sep 21 16:10 myfifo_mknod

*/