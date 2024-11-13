#include <stdio.h>
#include <signal.h>
#include <string.h>

void interrupt_handler(int signal_number) {
    printf("Mwuahaha, you can't escape! 💀\n");
}

int main(int argc, char *argv[]) {
    // Create the sigaction structure
    struct sigaction sa;
    sa.sa_handler = interrupt_handler; // Set the signal handler
    sigemptyset(&sa.sa_mask); // Don't block signals during handling
    sa.sa_flags = 0;  // Don't use special flags
    
    // Update signal handling behavior
    sigaction(SIGINT, &sa, NULL);

    while (1) {
    }

    return 0;
}