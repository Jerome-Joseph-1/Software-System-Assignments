/*
============================================================================
Name : 16.c
Author : Jerome Joseph
Description : Write a program to send and receive data from parent to child vice versa. Use two way
communication
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int parent_to_child[2];  
    int child_to_parent[2];  
    pid_t pid;
    char parent_msg[] = "Message from parent to child";
    char child_msg[] = "Message from child to parent";
    char buffer[100];

    pipe(parent_to_child);  
    pipe(child_to_parent);  

    pid = fork();

    if (pid > 0) {  
        close(parent_to_child[0]);  
        close(child_to_parent[1]);  

        write(parent_to_child[1], parent_msg, strlen(parent_msg) + 1);  
        close(parent_to_child[1]);  

        read(child_to_parent[0], buffer, sizeof(buffer));  
        printf("Parent received: %s\n", buffer);
        close(child_to_parent[0]);  
    } else if (pid == 0) {  
        close(parent_to_child[1]);  
        close(child_to_parent[0]);  

        read(parent_to_child[0], buffer, sizeof(buffer));  
        printf("Child received: %s\n", buffer);
        close(parent_to_child[0]);  

        write(child_to_parent[1], child_msg, strlen(child_msg) + 1);  
        close(child_to_parent[1]);  
    }

    return 0;
}

/*

❯ ./run.sh                                                                                                         ─╯
Child received: Message from parent to child
Parent received: Message from child to parent

*/