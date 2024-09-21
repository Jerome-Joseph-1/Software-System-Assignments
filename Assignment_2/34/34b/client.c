/*
============================================================================
Name : 34b.c
Author : Jerome Joseph
Description : Write a program to create a concurrent server.
        (CLIENT)
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         
#include <arpa/inet.h>      
#include <sys/socket.h>     

#define PORT 65432
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_sent, bytes_received;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <SERVER_IP_ADDRESS>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    memset(&(server_addr.sin_zero), '\0', 8); 
    
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server %s:%d\n", argv[1], PORT);
    printf("Type messages to send to the server. Type 'exit' to quit.\n");

    while (1) {
        printf("Client: ");
        fflush(stdout);
        memset(buffer, 0, BUFFER_SIZE);
        
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            perror("fgets");
            break;
        }
        
        bytes_sent = send(sock_fd, buffer, strlen(buffer), 0);
        if (bytes_sent < 0) {
            perror("send");
            break;
        }
        
        if (strcasecmp(buffer, "exit\n") == 0 || strcasecmp(buffer, "exit\r\n") == 0) {
            printf("Closing connection.\n");
            break;
        }
        
        memset(buffer, 0, BUFFER_SIZE);
        bytes_received = recv(sock_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received < 0) {
            perror("recv");
            break;
        } else if (bytes_received == 0) {
            printf("Server disconnected.\n");
            break;
        }

        printf("Server: %s\n", buffer);
    }

    close(sock_fd);
    return 0;
}

/*

❯ ./client 127.0.0.1                                                                                        ─╯
Connected to server 127.0.0.1:65432
Type messages to send to the server. Type 'exit' to quit.
Client: Hello World
Server: Hello World

Client: Nice
Server: Nice

Client: ^C

*/