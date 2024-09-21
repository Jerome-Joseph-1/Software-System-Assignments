/*
============================================================================
Name : 33.c
Author : Jerome Joseph
Description : Write a program to communicate between two machines using socket.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>        // close
#include <arpa/inet.h>     // sockaddr_in, inet_pton
#include <sys/socket.h>    // socket functions

#define PORT 65432
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <SERVER_IP_ADDRESS>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create socket file descriptor (IPv4, TCP)
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sock);
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr,
                sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server %s:%d\n", argv[1], PORT);

    // Communication loop
    while (1) {
        printf("Client: ");
        fflush(stdout);
        memset(buffer, 0, BUFFER_SIZE);
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            perror("fgets");
            break;
        }

        // Remove newline character from fgets
        buffer[strcspn(buffer, "\n")] = '\0';

        if (send(sock, buffer, strlen(buffer), 0) < 0) {
            perror("send");
            break;
        }

        // Optional: Exit condition
        if (strcasecmp(buffer, "exit") == 0) {
            printf("Exiting.\n");
            break;
        }

        memset(buffer, 0, BUFFER_SIZE);
        bytes_read = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_read <= 0) {
            if (bytes_read == 0) {
                printf("Server disconnected.\n");
            } else {
                perror("recv");
            }
            break;
        }

        printf("Server: %s\n", buffer);
    }

    // Clean up
    close(sock);
    return 0;
}
