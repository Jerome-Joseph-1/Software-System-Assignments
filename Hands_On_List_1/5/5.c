/*
============================================================================
Name : 5.c
Author : Jerome Joseph
Description : Write a program to create five new files with infinite loop. Execute the program in the background
and check the file descriptor table at /proc/pid/fd.
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pid = getpid();
    printf("PID: %d\n", pid);

    int fd[100];
    int file_num = 0;
    while(1) {
        char filename[100];
        printf("Enter the filename for file %d: ", file_num + 1);
        fgets(filename, 100, stdin);

        int file_descriptor = creat(filename, S_IRWXU);

        if(file_descriptor != -1) {
            fd[file_num++] = file_descriptor;
            printf("File created: %s", filename);
            printf("File descriptors: %d\n", file_descriptor);
        }
    }

    return 0;
}

/*
❯ ./main                                     ─╯
PID: 97297
Enter the filename for file 1: a
File created: a
File descriptors: 3
Enter the filename for file 2: b
File created: b
File descriptors: 4
Enter the filename for file 3: c
File created: c
File descriptors: 5
Enter the filename for file 4: d
File created: d
File descriptors: 6
Enter the filename for file 5: e
File created: e
File descriptors: 7
Enter the filename for file 6: 

============================================

❯ cd /proc/100969/fd

❯ ls                                      ─╯
0 1 2 3 4 5 6 7

*/