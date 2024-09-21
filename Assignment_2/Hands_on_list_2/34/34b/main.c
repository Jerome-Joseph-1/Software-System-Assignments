/*
============================================================================
Name : 34b.c
Author : Jerome Joseph
Description : Write a program to create a concurrent server.
        b. use pthread_create
Date: 21st September 2024
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>         
#include <arpa/inet.h>      
#include <sys/socket.h>     
#include <pthread.h>        

#define PORT 65432
#define BUFFER_SIZE 1024
#define BACKLOG 10          


typedef struct {
    int client_socket;
    struct sockaddr_in client_addr;
} client_info_t;


void *handle_client_thread(void *arg) {
    client_info_t *client_info = (client_info_t *)arg;
    int client_socket = client_info->client_socket;
    struct sockaddr_in client_addr = client_info->client_addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    printf("Connected to client: %s:%d\n", inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received < 0) {
            perror("recv");
            break;
        } else if (bytes_received == 0) {
            printf("Client disconnected: %s:%d\n", inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port));
            break;
        }

        printf("Client %s:%d: %s\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port), buffer);

        
        if (send(client_socket, buffer, strlen(buffer), 0) < 0) {
            perror("send");
            break;
        }

        
        if (strcasecmp(buffer, "exit\n") == 0 || strcasecmp(buffer, "exit\r\n") == 0) {
            printf("Closing connection with client: %s:%d\n", inet_ntoa(client_addr.sin_addr),
                   ntohs(client_addr.sin_port));
            break;
        }
    }

    close(client_socket);
    free(client_info);
    pthread_exit(NULL);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size;
    pthread_t tid;

    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) == -1) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    memset(&(server_addr.sin_zero), '\0', 8); 

    
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    
    if (listen(server_fd, BACKLOG) == -1) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    
    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &sin_size)) == -1) {
            perror("accept");
            continue;
        }

        
        client_info_t *client_info = malloc(sizeof(client_info_t));
        if (client_info == NULL) {
            perror("malloc");
            close(client_fd);
            continue;
        }

        client_info->client_socket = client_fd;
        client_info->client_addr = client_addr;

        
        if (pthread_create(&tid, NULL, handle_client_thread, (void *)client_info) != 0) {
            perror("pthread_create");
            close(client_fd);
            free(client_info);
            continue;
        }

        
        pthread_detach(tid);
    }

    
    close(server_fd);
    return 0;
}

/*

❯ ./run.sh                                                                                                  ─╯
Server listening on port 65432
Connected to client: 127.0.0.1:37406
Client 127.0.0.1:37406: HI

Client 127.0.0.1:37406: Hellow


❯ ./client 127.0.0.1                                                                                        ─╯
Connected to server 127.0.0.1:65432
Type messages to send to the server. Type 'exit' to quit.
Client: HI    
Server: HI

Client: Hellow
Server: Hellow

Client: 

*/