/*
============================================================================
Name : 30.c
Author : Jerome Joseph
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 31st Aug, 2024.
============================================================================
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void run_as_daemon()
{
    pid_t pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE); 
    if (pid > 0)
        exit(EXIT_SUCCESS);

    if (setsid() < 0)
        exit(EXIT_FAILURE); 
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);  

    umask(0); 
    chdir("/");  

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void wait_until(int hour, int minute)
{
    while (1)
    {
        time_t now = time(NULL);
        struct tm *current_time = localtime(&now);

        if (current_time->tm_hour == hour && current_time->tm_min == minute)
        {
            system("./script.sh");
            break;
        }
        sleep(60); 
    }
}

int main()
{
    run_as_daemon();

    int hour = 14;    
    int minute = 30;  

    wait_until(hour, minute);

    return 0;
}

/*

❯ gcc -o test_daemon_c 30.c                                                                     ─╯

❯ ./test_daemon_c                                                                               ─╯

❯ pgrep test_daemon_c                                                                           ─╯
215929


*/