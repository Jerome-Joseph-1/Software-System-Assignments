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
#include <string.h>
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

    printf("FIFO '%s' created. Waiting for readers...\n", FIFO_NAME);

    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Error opening FIFO for writing");
        exit(EXIT_FAILURE);
    }

    printf("Reader found. You can start typing messages.\n");
    printf("Type 'exit' to quit.\n");

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        if (write(fd, buffer, strlen(buffer) + 1) == -1) {
            perror("Error writing to FIFO");
            exit(EXIT_FAILURE);
        }
    }

    close(fd);

    printf("Writer exiting.\n");
    return 0;
}


/*

❯ ./run.sh                                                                                      ─╯
FIFO 'myfifo' created. Waiting for readers...
Reader found. You can start typing messages.
Type 'exit' to quit.
Enter message: Hello Program 2!
Enter message: Another Message 
Enter message: exit 
Writer exiting.


*/