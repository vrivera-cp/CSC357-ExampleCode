#include <stdio.h>
#include <signal.h>
#include <string.h>

void interrupt_handler(int signal_number) {
    printf("Mwuahaha, you can't escape! 💀\n");
}

int main(int argc, char *argv[]) {
    signal(SIGINT, interrupt_handler);
    while (1) {
        // printf("%ld\n", strlen("💀")); // If you're curious how this works in C
    }
}