/*
============================================================================
Name : 21.c
Author : Jerome Joseph
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
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

#define FIFO_A_TO_B "fifo_a_to_b"
#define FIFO_B_TO_A "fifo_b_to_a"
#define BUFFER_SIZE 256

int main() {
    int fd_write, fd_read;
    char buffer[BUFFER_SIZE];

    if (mkfifo(FIFO_A_TO_B, 0666) == -1 && errno != EEXIST) {
        perror("Error creating FIFO_A_TO_B");
        exit(EXIT_FAILURE);
    }

    if (mkfifo(FIFO_B_TO_A, 0666) == -1 && errno != EEXIST) {
        perror("Error creating FIFO_B_TO_A");
        exit(EXIT_FAILURE);
    }

    printf("Program A started.\n");

    fd_write = open(FIFO_A_TO_B, O_WRONLY);
    if (fd_write == -1) {
        perror("Program A: Error opening FIFO_A_TO_B for writing");
        exit(EXIT_FAILURE);
    }

    fd_read = open(FIFO_B_TO_A, O_RDONLY);
    if (fd_read == -1) {
        perror("Program A: Error opening FIFO_B_TO_A for reading");
        exit(EXIT_FAILURE);
    }

    printf("Connected to Program B.\n");
    printf("Type 'exit' to quit.\n");

    while (1) {
        printf("Program A: Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        if (write(fd_write, buffer, strlen(buffer) + 1) == -1) {
            perror("Program A: Error writing to FIFO_A_TO_B");
            break;
        }

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        if (read(fd_read, buffer, BUFFER_SIZE) == -1) {
            perror("Program A: Error reading from FIFO_B_TO_A");
            break;
        }

        if (strcmp(buffer, "exit") == 0) {
            printf("Program B has exited.\n");
            break;
        }

        printf("Program B says: %s\n", buffer);
    }

    close(fd_write);
    close(fd_read);

    printf("Program A exiting.\n");
    return 0;
}

/*

❯ ./run.sh                                                                                                  ─╯
Program A started.
Connected to Program B.
Type 'exit' to quit.
Program A: Enter message: Hi
Program B says: Hello Program A!
Program A: Enter message: Assignment done ? 
Program B says: Noooooo
Program A: Enter message: ^C

*/