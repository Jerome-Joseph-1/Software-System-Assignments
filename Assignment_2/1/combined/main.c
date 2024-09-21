/*
============================================================================
Name : -
Author : Jerome Joseph
Description : Combined Real, Virtual and Prof timers
Date: 21st September 2024
============================================================================
*/

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    struct itimerval real_start, real_end;
    struct itimerval virt_start, virt_end;
    struct itimerval prof_start, prof_end;

    struct itimerval max_timer;
    max_timer.it_value.tv_sec = 1000;
    max_timer.it_value.tv_usec = 0;
    max_timer.it_interval.tv_sec = 0;
    max_timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &max_timer, NULL) == -1) {
        perror("Error setting ITIMER_REAL");
        return 1;
    }
    if (setitimer(ITIMER_VIRTUAL, &max_timer, NULL) == -1) {
        perror("Error setting ITIMER_VIRTUAL");
        return 1;
    }
    if (setitimer(ITIMER_PROF, &max_timer, NULL) == -1) {
        perror("Error setting ITIMER_PROF");
        return 1;
    }

    if (getitimer(ITIMER_REAL, &real_start) == -1) {
        perror("Error getting ITIMER_REAL");
        return 1;
    }
    if (getitimer(ITIMER_VIRTUAL, &virt_start) == -1) {
        perror("Error getting ITIMER_VIRTUAL");
        return 1;
    }
    if (getitimer(ITIMER_PROF, &prof_start) == -1) {
        perror("Error getting ITIMER_PROF");
        return 1;
    }

    for (int i = 0; i < 100000000; ++i) {
        volatile double x = 0.999999 + i;
    }

    FILE *fp = fopen("testfile.txt", "w");
    if (fp == NULL) {
        perror("Error creating testfile.txt");
        return 1;
    }

    for (int i = 0; i < 100000; ++i) {
        fprintf(fp, "This is line %d\n", i);
    }
    fclose(fp);

    fp = fopen("testfile.txt", "r");
    if (fp == NULL) {
        perror("Error opening testfile.txt");
        return 1;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Reading lines 
    }
    fclose(fp);

    if (remove("testfile.txt") != 0) {
        perror("Error deleting testfile.txt");
        return 1;
    }

    if (getitimer(ITIMER_REAL, &real_end) == -1) {
        perror("Error getting ITIMER_REAL");
        return 1;
    }
    if (getitimer(ITIMER_VIRTUAL, &virt_end) == -1) {
        perror("Error getting ITIMER_VIRTUAL");
        return 1;
    }
    if (getitimer(ITIMER_PROF, &prof_end) == -1) {
        perror("Error getting ITIMER_PROF");
        return 1;
    }

    double real_time = (real_start.it_value.tv_sec - real_end.it_value.tv_sec) +
                       (real_start.it_value.tv_usec - real_end.it_value.tv_usec) / 1e6;

    double user_time = (virt_start.it_value.tv_sec - virt_end.it_value.tv_sec) +
                       (virt_start.it_value.tv_usec - virt_end.it_value.tv_usec) / 1e6;

    double prof_time = (prof_start.it_value.tv_sec - prof_end.it_value.tv_sec) +
                       (prof_start.it_value.tv_usec - prof_end.it_value.tv_usec) / 1e6;

    double sys_time = prof_time - user_time;

    printf("Real Time Elapsed: %f seconds\n", real_time);
    printf("User CPU Time: %f seconds\n", user_time);
    printf("System CPU Time: %f seconds\n", sys_time);

    return 0;
}
