/*
============================================================================
Name : 18.c
Author : Jerome Joseph
Description : Write a program to perform Record locking.
    a. Implement write lock
    b. Implement read lock
    -  Create three records in a file. Whenever you access a particular record, first lock it then modify/access
    to avoid race condition.
Date: 31st Aug, 2024.
============================================================================
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RECORD_SIZE 100  // Size of each record
#define NUM_RECORDS 4    // Number of records

typedef struct {
    char data[RECORD_SIZE];
} Record;

void write_lock(int fd, off_t offset, off_t length) {
    struct flock lock = {
        .l_type = F_WRLCK,
        .l_whence = SEEK_SET,
        .l_start = offset,
        .l_len = length
    };

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to acquire write lock");
        exit(-1);
    }
}

void write_unlock(int fd, off_t offset, off_t length) {
    struct flock lock = {
        .l_type = F_UNLCK,
        .l_whence = SEEK_SET,
        .l_start = offset,
        .l_len = length
    };

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to release write lock");
        exit(-1);
    }
}

void read_lock(int fd, off_t offset, off_t length) {
    struct flock lock = {
        .l_type = F_RDLCK,
        .l_whence = SEEK_SET,
        .l_start = offset,
        .l_len = length
    };

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to acquire read lock");
        exit(-1);
    }
}

void read_unlock(int fd, off_t offset, off_t length) {
    struct flock lock = {
        .l_type = F_UNLCK,
        .l_whence = SEEK_SET,
        .l_start = offset,
        .l_len = length
    };

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Failed to release read lock");
        exit(-1);
    }
}

void display_record(int fd, int index) {
    off_t offset = index * RECORD_SIZE;
    Record record;

    read_lock(fd, offset, RECORD_SIZE);

    lseek(fd, offset, SEEK_SET);
    if (read(fd, &record, sizeof(record)) == -1) {
        perror("Failed to read record");
        read_unlock(fd, offset, RECORD_SIZE);
        exit(-1);
    }

    printf("Record %d: %s\n", index + 1, record.data);

    read_unlock(fd, offset, RECORD_SIZE);
}

void modify_record(int fd, int index, int record_num) {
    off_t offset = index * RECORD_SIZE;

    write_lock(fd, offset, RECORD_SIZE);

    char new_data[RECORD_SIZE];

    printf("Enter new data for record %d: ", record_num);
    scanf(" %[^\n]", new_data);

    Record record;
    strncpy(record.data, new_data, RECORD_SIZE - 1);
    record.data[RECORD_SIZE - 1] = '\0';

    lseek(fd, offset, SEEK_SET);
    if (write(fd, &record, sizeof(record)) == -1) {
        perror("Failed to write record");
        write_unlock(fd, offset, RECORD_SIZE);
        exit(-1);
    }

    write_unlock(fd, offset, RECORD_SIZE);
}

int main() {
    int fd = open("records", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return -1;
    }

    int choice, record_num;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Display a record\n");
        printf("2. Modify a record\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        while(getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter record number to display (1-%d): ", NUM_RECORDS);
                scanf("%d", &record_num);
                if (record_num >= 1 && record_num <= NUM_RECORDS) {
                    display_record(fd, record_num - 1);
                } else {
                    printf("Invalid record number.\n");
                }
                break;

            case 2:
                printf("Enter record number to modify (1-%d): ", NUM_RECORDS);
                scanf("%d", &record_num);
                if (record_num >= 1 && record_num <= NUM_RECORDS) {
                    modify_record(fd, record_num - 1, record_num);
                } else {
                    printf("Invalid record number.\n");
                }
                break;

            case 3:
                close(fd);
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

/*

❯ ./main                                                                                        ─╯

Menu:
1. Display a record
2. Modify a record
3. Exit
Enter your choice: 1
Enter record number to display (1-4): 1
Record 1: SOME RANDOM DATA

Menu:
1. Display a record
2. Modify a record
3. Exit
Enter your choice: 2
Enter record number to modify (1-4): 1
Enter new data for record 1: new data

Menu:
1. Display a record
2. Modify a record
3. Exit
Enter your choice: 1
Enter record number to display (1-4): 1
Record 1: new data

Menu:
1. Display a record
2. Modify a record
3. Exit
Enter your choice: 


*/