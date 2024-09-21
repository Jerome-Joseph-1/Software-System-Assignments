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

    printf("Program B started.\n");

    fd_read = open(FIFO_A_TO_B, O_RDONLY);
    if (fd_read == -1) {
        perror("Program B: Error opening FIFO_A_TO_B for reading");
        exit(EXIT_FAILURE);
    }

    fd_write = open(FIFO_B_TO_A, O_WRONLY);
    if (fd_write == -1) {
        perror("Program B: Error opening FIFO_B_TO_A for writing");
        exit(EXIT_FAILURE);
    }

    printf("Connected to Program A.\n");
    printf("Type 'exit' to quit.\n");

    while (1) {
        if (read(fd_read, buffer, BUFFER_SIZE) == -1) {
            perror("Program B: Error reading from FIFO_A_TO_B");
            break;
        }

        if (strcmp(buffer, "exit") == 0) {
            printf("Program A has exited.\n");
            break;
        }

        printf("Program A says: %s\n", buffer);

        printf("Program B: Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        if (write(fd_write, buffer, strlen(buffer) + 1) == -1) {
            perror("Program B: Error writing to FIFO_B_TO_A");
            break;
        }

        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    close(fd_write);
    close(fd_read);

    printf("Program B    exiting.\n");
    return 0;
}

/*

❯ gcc -o temp main2.c && ./temp                                                                                    ─╯
Program B started.
Connected to Program A.
Type 'exit' to quit.
Program A says: Hi
Program B: Enter message: Hello Program A!
Program A says: Assignment done ? 
Program B: Enter message: Noooooo
Program A says: Noooooo
Program B: Enter message: ^C

*/