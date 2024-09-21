/*
============================================================================
Name : 15.c
Author : Jerome Joseph
Description : Write a program to display the environmental variable of the user (use environ).
Date: 31st Aug, 2024.
============================================================================
*/

#include <stdio.h>

extern char **environ;

int main() {
    while(*environ != NULL) {
        printf("%s\n", *environ);
        environ++;
    }
    return 0;
}


/*
❯ ./main                                                                                        ─╯
BROWSER=firefox
COLORFGBG=15;0
COLORTERM=truecolor
DISPLAY=:1
...
*/