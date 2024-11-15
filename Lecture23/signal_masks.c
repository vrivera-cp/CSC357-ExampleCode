#include <signal.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void signal_handler(int signo) {
    printf("Caught signal %d\n", signo);
}

int main(int argc, char *argv[]) {
    // Set handler
    signal(SIGINT, signal_handler);

    // Create a signal set to block SIGINT
    sigset_t new_set, old_set;

    // Initialize the new signal set
    sigemptyset(&new_set);
    sigaddset(&new_set, SIGINT);

    // Block SIGINT signals
    if (sigprocmask(SIG_BLOCK, &new_set, &old_set) == -1) {
        perror("Could not set signal mask");
        exit(1);
    }

    // Simulate a "critical section" of code that shouldn't be interrupted
    printf("Critical Section Begin\n");
    sleep(5);
    printf("Critical Section End\n");

    // Reset mask
    if (sigprocmask(SIG_SETMASK, &old_set, NULL) == -1) {
        perror("sigprocmask");
        exit(1);
    }

    // Simulate non "critical section"
    printf("Non-Critical Section Begin\n");
    sleep(5);
    printf("Non-Critical Section End\n");
    
    return EXIT_SUCCESS;
}