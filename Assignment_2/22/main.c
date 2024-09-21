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
#include <sys/select.h>
#include <string.h>
#include <errno.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 256
#define TIMEOUT_SECONDS 10

int main() {
    int fifo_fd;
    char buffer[BUFFER_SIZE];
    fd_set read_fds;
    struct timeval timeout;
    int retval;

    if (mkfifo(FIFO_NAME, 0666) == -1) {
        if (errno != EEXIST) {
            perror("Error creating FIFO");
            exit(EXIT_FAILURE);
        }
    }

    printf("FIFO '%s' created/opened for reading.\n", FIFO_NAME);
    printf("Waiting for data with a timeout of %d seconds...\n", TIMEOUT_SECONDS);

    fifo_fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
    if (fifo_fd == -1) {
        perror("Error opening FIFO for reading");
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&read_fds);
    FD_SET(fifo_fd, &read_fds);

    timeout.tv_sec = TIMEOUT_SECONDS;
    timeout.tv_usec = 0;

    retval = select(fifo_fd + 1, &read_fds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select() error");
        close(fifo_fd);
        exit(EXIT_FAILURE);
    } else if (retval == 0) {
        printf("No data received within %d seconds. Timeout occurred.\n", TIMEOUT_SECONDS);
    } else {
        if (FD_ISSET(fifo_fd, &read_fds)) {
            ssize_t bytes_read = read(fifo_fd, buffer, BUFFER_SIZE - 1);
            if (bytes_read == -1) {
                perror("Error reading from FIFO");
                close(fifo_fd);
                exit(EXIT_FAILURE);
            } else if (bytes_read == 0) {
                printf("No writers connected. Exiting.\n");
            } else {
                buffer[bytes_read] = '\0';
                printf("Received message: %s\n", buffer);
            }
        }
    }

    close(fifo_fd);

    printf("Reader program exiting.\n");
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