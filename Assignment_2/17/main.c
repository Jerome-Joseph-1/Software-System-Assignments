/*
============================================================================
Name : 17.c
Author : Jerome Joseph
Description : Write a program to execute ls -l | wc.
        a. use dup
        b. use dup2
        c. use fcntl
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) < 0) {
        perror("pipe error");
        exit(1);
    }
    
    if ((pid = fork()) == 0) { 
        close(fd[0]); 

        close(1); 
        if (fcntl(fd[1], F_DUPFD, 1) != 1) { 
            perror("fcntl error");
            exit(1);
        }
        close(fd[1]); 
        
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls error");
        exit(1);
    } else if (pid > 0) { 
        
        if ((pid = fork()) == 0) {
            close(fd[1]); 
            
            close(0); 
            if (fcntl(fd[0], F_DUPFD, 0) != 0) { 
                perror("fcntl error");
                exit(1);
            }
            close(fd[0]); 

            
            execlp("wc", "wc", (char *)NULL);
            perror("execlp wc error");
            exit(1);
        } else if (pid > 0) {
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            wait(NULL);
        } else {
            perror("fork error");
            exit(1);
        }
    } else {
        perror("fork error");
        exit(1);
    }

    return 0;
}


/*

❯ ./run.sh                                                                                                         ─╯
      5      38     218

*/