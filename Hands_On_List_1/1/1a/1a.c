/*
============================================================================
Name : 1a.c
Author : Jerome Joseph
Description : Create the following types of a files using system call
    a. soft link (symlink system call)
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h> 

int main(int argc, char** argv) {
    if(argc == 3) {
        char* target = argv[1];
        char* linkpath = argv[2];

        int retval = symlink(target, linkpath);
        if(retval == 0)
            printf("Symlink created successfully!\n");
        else 
            perror("Error");
    } else {
        printf("Usage: [executable] [filename1] [filename2]\nfilename1: target file\nfilename2: linkpath\n");
    }

    return 0;
}

/* OUTPUT 

 ~/Documents/Code/Assignments/System Software/1/1a ▓▒░                                                ░▒▓ 19:17:44 ─╮
❯ gcc -o main 1a.c                                                                                                 ─╯

 ~/Documents/Code/Assignments/System Software/1/1a ▓▒░                                                ░▒▓ 19:17:53 ─╮
❯ ./main                                                                                                       ─╯
Usage: [executable] [filename1] [filename2]
filename1: target file
filename2: linkpath

 ~/Documents/Code/Assignments/System Software/1/1a ▓▒░                                                ░▒▓ 19:17:54 ─╮
❯ ls -l                                                                                                         ─╯
total 24
-rw-r--r-- 1 jerome jerome   476 Aug 30 19:08 1a.c
-rw-r--r-- 1 jerome jerome    27 Aug 30 19:12 file1
lrwxrwxrwx 1 jerome jerome     5 Aug 30 19:08 file2 -> file1
-rwxr-xr-x 1 jerome jerome 15520 Aug 30 19:17 main
-rw-r--r-- 1 jerome jerome     0 Aug 30 19:17 shell_command.sh

 ~/Documents/Code/Assignments/System Software/1/1a ▓▒░                                                ░▒▓ 19:17:58 ─╮
❯ ./main file1 file3                                                                                               ─╯
Symlink created successfully!

 ~/Documents/Code/Assignments/System Software/1/1a ▓▒░                                                ░▒▓ 19:18:07 ─╮
❯ ls -ali file1 file3                                                                                                       ─╯
13501087 -rw-r--r-- 2 jerome jerome 28 Aug 30 19:19 file1
13501381 lrwxrwxrwx 1 jerome jerome  5 Aug 30 19:18 file3 -> file1

~/Documents/Code/Assignments/System Software/1/1a ▓▒░                                                        ░▒▓ 19:19:26 ─╮
❯ cat file1                                                                                                                ─╯
THIS HAS SOME CONTENT IN IT

 ~/Documents/Code/Assignments/System Software/1/1a ▓▒░                                                        ░▒▓ 19:19:36 ─╮
❯ cat file3                                                                                                                ─╯
THIS HAS SOME CONTENT IN IT
                                                                                                                  
*/