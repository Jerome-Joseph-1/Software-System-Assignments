/*
============================================================================
Name : 20.c
Author : Jerome Joseph
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
    #include <errno.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 256

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    if (mkfifo(FIFO_NAME, 0666) == -1) {
        if (errno != EEXIST) {
            perror("Error creating FIFO");
            exit(EXIT_FAILURE);
        }
    }

    printf("FIFO '%s' created. Waiting for writers...\n", FIFO_NAME);

    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        exit(EXIT_FAILURE);
    }

    printf("Writer connected. Waiting for messages...\n");
    printf("Press Ctrl+C to exit.\n");

    while (1) {
        ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE);
        if (bytesRead == -1) {
            perror("Error reading from FIFO");
            exit(EXIT_FAILURE);
        } else if (bytesRead == 0) {
            sleep(1);
            continue;
        }

        printf("Received message: %s\n", buffer);
    }

    close(fd);

    printf("Reader exiting.\n");
    return 0;
}

/*

❯ gcc -o reader reader.c && ./reader                                                                                                  ─╯
FIFO 'myfifo' created. Waiting for writers...
Writer connected. Waiting for messages...
Press Ctrl+C to exit.
Received message: Hello Program 2!
Received message: Another Message 

*/