/*
============================================================================
Name : 1b.c
Author : Jerome Joseph
Description : Create the following types of a files using system call
    b. hard link (link system call)
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if(argc == 3) {
        char* oldpath = argv[1];
        char* newpath = argv[2];

        int retval = link(oldpath, newpath);
        if(retval == 0)
            printf("Hard link created successfully!\n");
        else 
            perror("Error");
    } else {
        printf("Usage: [executable] [filename1] [filename2]\nfilename1: oldpath\nfilename2: newpath\n");
    }

    return 0;
}


/*
❯ ls -il file1                                                                                                             ─╯
13501368 -rw-r--r-- 2 jerome jerome 17 Aug 30 19:16 file1

❯ gcc -o main 1b.c                                                                                                         ─╯

❯ ./main                                                                                                                   ─╯
Usage: [executable] [filename1] [filename2]
filename1: oldpath
filename2: newpath

❯ ./main file1 file2                                                                                                       ─╯
Hard link created successfully!

❯ ls -il file1 file2                                                                                                       ─╯
13501368 -rw-r--r-- 3 jerome jerome 17 Aug 30 19:16 file1
13501368 -rw-r--r-- 3 jerome jerome 17 Aug 30 19:16 file2

*/