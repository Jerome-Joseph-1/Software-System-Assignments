/*
============================================================================
Name : 19.c
Author : Jerome Joseph
Description : Create a FIFO file by
        a. mknod command
        b. mkfifo command
        c. use strace command to find out, which command (mknod or mkfifo) is better.
        c. mknod system call
Date: 21st September 2024
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *fifo_path = "myfifo_mknod";
    int result;

    result = mknod(fifo_path, S_IFIFO | 0666, 0);
    if (result == -1) {
        perror("Error creating FIFO with mknod");
        return errno;
    }

    printf("FIFO '%s' created using mknod system call.\n", fifo_path);
    return 0;
}


/*

❯ mknod myfifo p                                                                                ─╯
❯ ls -l myfifo                                                                                  ─╯
prw-r--r-- 1 jerome jerome 0 Sep 21 15:44 myfifo
-------------------------------------------------------------------
❯ mkfifo myfifo2                                                                                ─╯
❯ ls -l myfifo2                                                                                 ─╯
prw-r--r-- 1 jerome jerome 0 Sep 21 15:44 myfifo2
-------------------------------------------------------------------
❯ strace -e trace=file mknod myfifo_1 p                                                         ─╯

execve("/usr/bin/mknod", ["mknod", "myfifo_1", "p"], 0x7fff50612380 / * 77 vars *\/) = 0
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/usr/lib/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
mknodat(AT_FDCWD, "myfifo_1", S_IFIFO|0666) = 0
+++ exited with 0 +++
-------------------------------------------------------------------
❯ strace -e trace=file mkfifo myfifo_2                                                          ─╯

execve("/usr/bin/mkfifo", ["mkfifo", "myfifo_2"], 0x7ffcf21f0238 / * 77 vars *\/) = 0
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/usr/lib/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
mknodat(AT_FDCWD, "myfifo_2", S_IFIFO|0666) = 0
+++ exited with 0 +++
-------------------------------------------------------------------
❯ ./run.sh                                                                                      ─╯
FIFO 'myfifo_mknod' created using mknod system call.
-------------------------------------------------------------------
❯ ls -al myfifo_mkfifo myfifo_mknod                                                             ─╯
prw-r--r-- 1 jerome jerome 0 Sep 21 16:11 myfifo_mkfifo
prw-r--r-- 1 jerome jerome 0 Sep 21 16:10 myfifo_mknod

*/