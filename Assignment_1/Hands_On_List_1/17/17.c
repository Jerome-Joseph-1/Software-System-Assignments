/*
============================================================================
Name : 17.c
Author : Jerome Joseph
Description : Write a program to simulate online ticket reservation. 
    Implement write lock and read lock
    Write a program to open a file, store a ticket number and exit. 
    Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
Date: 31st Aug, 2024.
============================================================================
*/

#include "train_struct.c"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void read_db(int fd, Train_DB* trains, int size) {
    lseek(fd, 0, SEEK_SET);
    if (read(fd, trains, size) != size) {
        perror("Error reading from file");
        close(fd);
        exit(-1);
    }
}

int main() {
    int fd = open("db", O_RDWR);
    if (fd < 0) {
        perror("Error opening file");
        return -1;
    }

    Train_DB trains[3];
    read_db(fd, trains, sizeof(trains));

    int train_no_index_map[1000000] = {0};  
    for (int i = 0; i < 3; i++) {
        train_no_index_map[trains[i].train_number] = i;
    }

    while (1) {
        printf("Available trains:\n");
        for (int i = 0; i < 3; i++) {
            printf("Train Number: %d, Train Name: %s\n", trains[i].train_number, trains[i].train_name);
        }

        printf("Enter train number to book a ticket or 0 to exit: ");
        int train_number;
        if (scanf("%d", &train_number) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (train_number == 0) {
            break;
        }

        if (train_no_index_map[train_number] == 0 && train_number != trains[0].train_number) {
            printf("Invalid train number. Please try again.\n");
            continue;
        }

        int index = train_no_index_map[train_number];

        off_t offset = index * sizeof(Train_DB);
        write_lock(fd, offset, sizeof(Train_DB));
        read_db(fd, trains, sizeof(trains));

        printf("Current ticket count for train %d (%s): %d\n",
               trains[index].train_number,
               trains[index].train_name,
               trains[index].tickets_booked);

        while(getchar() != '\n');
        printf("Enter y to register a new ticket...: ");
        char choice;
        fscanf(stdin, "%c", &choice);    
        if(choice == 'y' || choice == 'Y') {
            trains[index].tickets_booked++;

            lseek(fd, offset, SEEK_SET);
            if (write(fd, &trains[index], sizeof(Train_DB)) != sizeof(Train_DB)) {
                perror("Error writing to file");
                write_unlock(fd, offset, sizeof(Train_DB));
                close(fd);
                return -1;  
            }
        }

        write_unlock(fd, offset, sizeof(Train_DB)); 
    }

    close(fd);
    return 0;
}


/*

❯ ./main                                                                                        ─╯
Available trains:
Train Number: 123, Train Name: EXPRESS A
Train Number: 235, Train Name: EXPRESS B
Train Number: 568, Train Name: EXPRESS C
Enter train number to book a ticket or 0 to exit: 235
Current ticket count for train 235 (EXPRESS B): 6
Enter y to register a new ticket...: y

Available trains:
Train Number: 123, Train Name: EXPRESS A
Train Number: 235, Train Name: EXPRESS B
Train Number: 568, Train Name: EXPRESS C
Enter train number to book a ticket or 0 to exit: 235
Current ticket count for train 235 (EXPRESS B): 7
Enter y to register a new ticket...: n

Available trains:
Train Number: 123, Train Name: EXPRESS A
Train Number: 235, Train Name: EXPRESS B
Train Number: 568, Train Name: EXPRESS C
Enter train number to book a ticket or 0 to exit: 235
Current ticket count for train 235 (EXPRESS B): 7
Enter y to register a new ticket...: y

Available trains:
Train Number: 123, Train Name: EXPRESS A
Train Number: 235, Train Name: EXPRESS B
Train Number: 568, Train Name: EXPRESS C
Enter train number to book a ticket or 0 to exit: 235
Current ticket count for train 235 (EXPRESS B): 8
Enter y to register a new ticket...: ^C


*/