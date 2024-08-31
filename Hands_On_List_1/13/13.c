/*
============================================================================
Name : 13.c
Author : Jerome Joseph
Description : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
verify whether the data is available within 10 seconds or not (check in $man 2 select).
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

int main() {
    struct timeval timeout;
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input for up to 10 seconds...\n");

    int result = select(1 /*highest fd + 1*/, &readfds, NULL, NULL, &timeout);

    if (result == -1) {
        perror("select");
        return -1;
    } else if (result == 0) {
        printf("No data received within 10 seconds.\n");
    } else if (FD_ISSET(STDIN_FILENO, &readfds)) {
        printf("Data received within 10 seconds!\n");
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("Received input: %s", buffer);
        }
    }

    return 0;
}


/*
❯ ./main                                                                                        ─╯
Waiting for input for up to 10 seconds...
jbdsfg dbsgfkj l
Data received within 10 seconds!
Received input: jbdsfg dbsgfkj l

❯ ./main                                                                                        ─╯
Waiting for input for up to 10 seconds...
No data received within 10 seconds.

*/