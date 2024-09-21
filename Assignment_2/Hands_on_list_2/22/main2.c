/*
============================================================================
Name : 22.c
Author : Jerome Joseph
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 256

int main() {
    int fifo_fd;
    char buffer[BUFFER_SIZE];

    
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        if (errno != EEXIST) {
            perror("Error creating FIFO");
            exit(EXIT_FAILURE);
        }
    }

    printf("FIFO '%s' created/opened for writing.\n", FIFO_NAME);

    
    fifo_fd = open(FIFO_NAME, O_WRONLY);
    if (fifo_fd == -1) {
        perror("Error opening FIFO for writing");
        exit(EXIT_FAILURE);
    }

    printf("Connected to Reader. You can start sending messages.\n");
    printf("Type 'exit' to quit.\n");

        
    printf("Enter message: ");
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        perror("Error reading input");
    }

    
    buffer[strcspn(buffer, "\n")] = '\0';

    
    if (write(fifo_fd, buffer, strlen(buffer) + 1) == -1) {
        perror("Error writing to FIFO");
    }

    
    if (strcmp(buffer, "exit") == 0) {
        printf("Exiting Writer.\n");
    }

    close(fifo_fd);

    return 0;
}


/*

❯ ./run.sh
FIFO 'myfifo' created/opened for reading.
Waiting for data with a timeout of 10 seconds...
Received message: Hiiiii
Reader program exiting.
-----
❯ ./temp                                                                                                    ─╯
FIFO 'myfifo' created/opened for writing.
Connected to Reader. You can start sending messages.
Type 'exit' to quit.
Enter message: Hiiiii
--------

❯ ./run.sh                                                                                                  ─╯
FIFO 'myfifo' created/opened for reading.
Waiting for data with a timeout of 10 seconds...
No data received within 10 seconds. Timeout occurred.
Reader program exiting.
-----------

*/
