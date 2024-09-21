/*
============================================================================
Name : 18.c
Author : Jerome Joseph
Description :   Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pipe1[2]; 
    int pipe2[2]; 
    pid_t pid1, pid2, pid3;

    
    if (pipe(pipe1) == -1) {
        perror("pipe1 error");
        exit(1);
    }

    
    if ((pid1 = fork()) == 0) {
        
        if (dup2(pipe1[1], STDOUT_FILENO) == -1) {
            perror("dup2 error ls");
            exit(1);
        }
        
        close(pipe1[0]); 
        close(pipe1[1]); 

        
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls error");
        exit(1);
    } else if (pid1 < 0) {
        perror("fork1 error");
        exit(1);
    }

    
    if (pipe(pipe2) == -1) {
        perror("pipe2 error");
        exit(1);
    }

    
    if ((pid2 = fork()) == 0) {
        
        if (dup2(pipe1[0], STDIN_FILENO) == -1) {
            perror("dup2 error grep stdin");
            exit(1);
        }
        
        if (dup2(pipe2[1], STDOUT_FILENO) == -1) {
            perror("dup2 error grep stdout");
            exit(1);
        }
        
        close(pipe1[0]); 
        close(pipe1[1]); 
        close(pipe2[0]); 
        close(pipe2[1]); 

        
        execlp("grep", "grep", "^d", NULL);
        perror("execlp grep error");
        exit(1);
    } else if (pid2 < 0) {
        perror("fork2 error");
        exit(1);
    }

    
    close(pipe1[0]);
    close(pipe1[1]);

    
    if ((pid3 = fork()) == 0) {
        
        if (dup2(pipe2[0], STDIN_FILENO) == -1) {
            perror("dup2 error wc");
            exit(1);
        }
        
        close(pipe2[0]); 
        close(pipe2[1]); 

        
        execlp("wc", "wc", NULL);
        perror("execlp wc error");
        exit(1);
    } else if (pid3 < 0) {
        perror("fork3 error");
        exit(1);
    }

    
    close(pipe2[0]);
    close(pipe2[1]);

    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}

/*

❯ ./run.sh                                                                                                         ─╯
      2      18     105

❯  ls -l | grep ^d | wc                                                                                            ─╯
      2      18     105

*/