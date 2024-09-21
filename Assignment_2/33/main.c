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
#include <unistd.h>       
#include <arpa/inet.h>    
#include <sys/socket.h>   

#define PORT 65432
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    int opt = 1;
    ssize_t bytes_read;

    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);

    
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             &addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected by %s:%d\n", inet_ntoa(address.sin_addr),
           ntohs(address.sin_port));

    
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        bytes_read = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_read <= 0) {
            if (bytes_read == 0) {
                printf("Client disconnected.\n");
            } else {
                perror("recv");
            }
            break;
        }

        printf("Client: %s\n", buffer);

        printf("Server: ");
        fflush(stdout);
        memset(buffer, 0, BUFFER_SIZE);
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            perror("fgets");
            break;
        }

        
        buffer[strcspn(buffer, "\n")] = '\0';

        if (send(new_socket, buffer, strlen(buffer), 0) < 0) {
            perror("send");
            break;
        }

        
        if (strcasecmp(buffer, "exit") == 0) {
            printf("Exiting.\n");
            break;
        }
    }

    
    close(new_socket);
    close(server_fd);
    return 0;
}


/*

❯ ./client 127.0.0.1
Connected to server 127.0.0.1:65432
Client: Hi
Server: Yo
Client: HMmm
^C

❯ ./run.sh                                                                                                                          ─╯
Server listening on port 65432
Connected by 127.0.0.1:35616
Client: Hi
Server: Yo
Client: HMmm
Server: Iiu
Client disconnected.

*/