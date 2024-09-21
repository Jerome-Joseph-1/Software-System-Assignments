/*
============================================================================
Name : 16.c
Author : Jerome Joseph
Description : Write a program to perform mandatory locking.
    a. Implement write lock
    b. Implement read lock  
Date: 31st Aug, 2024.
============================================================================
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int read_lock_count = 0;
int write_lock_count = 0;

void write_lock(int fd) {
    struct flock w_lock = {
        .l_type = F_WRLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0
    };

    if (fcntl(fd, F_SETLKW, &w_lock) == -1) {
        perror("Failed to acquire write lock");
    }
    write_lock_count++;
    printf("Write lock acquired. Total write locks: %d\n", write_lock_count);
}

void read_lock(int fd) {
    struct flock r_lock = {
        .l_type = F_RDLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0
    };

    if (fcntl(fd, F_SETLKW, &r_lock) == -1) {
        perror("Failed to acquire read lock");
    }
    read_lock_count++;
    printf("Read lock acquired. Total read locks: %d\n", read_lock_count);
}

void unlock_read(int fd) {
    struct flock lock = {
        .l_type = F_UNLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0
    };

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to release read lock");
    }
    read_lock_count--;
    printf("Read lock released. Total read locks: %d\n", read_lock_count);
}

void unlock_write(int fd) {
    struct flock lock = {
        .l_type = F_UNLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0
    };

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to release write lock");
    }
    write_lock_count--;
    printf("Write lock released. Total write locks: %d\n", write_lock_count);
}

int main() {
    int fd = open("file1", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Failed to open file");
    }

    read_lock(fd);
    sleep(3);   

    read_lock(fd);
    sleep(3);

    unlock_read(fd);
    sleep(1);

    unlock_read(fd);

    write_lock(fd);
    sleep(3);

    unlock_write(fd);

    close(fd);
    return 0;
}


/*

❯ ./main                                                                                        
Read lock acquired. Total read locks: 1
Read lock acquired. Total read locks: 2
Read lock released. Total read locks: 1
Read lock released. Total read locks: 0
Write lock acquired. Total write locks: 1
Write lock released. Total write locks: 0

*/