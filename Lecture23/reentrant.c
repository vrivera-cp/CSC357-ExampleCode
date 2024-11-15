#include <signal.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void alarm_handler(int signo) {
    int *array = malloc(sizeof(int) * 1000);
    array[500] = 2000;
    printf("%d\n", array[500]);
}

int main(int argc, char *argv[]) {
    // Set handler
    signal(SIGALRM, alarm_handler);

    // Set up the interval timer
    struct itimerval timer;
    
    // Set timer interval (1 second)
    timer.it_interval.tv_sec = 1;    // Interval: 1 second
    timer.it_interval.tv_usec = 0;   // No microseconds
    
    // Set timer to first fire after 1 second
    timer.it_value.tv_sec = 1;       // Initial delay: 1 second
    timer.it_value.tv_usec = 0;      // No microseconds

    // Set the timer using setitimer()
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Error setting timer");
        exit(1);
    }

    // Perform non-reentrant logic
    for (long i = 0; i < 9999999999999; i++) {
        int *value = malloc(sizeof(int) * 10000);
        if (value != NULL) free(value);
    }

    return 0;
}