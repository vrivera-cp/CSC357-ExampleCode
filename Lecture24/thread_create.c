#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_function(void *data) {
    printf("I'm the thread, my data is: %d\n", *((int *) data));

    return NULL; // Unused    
}

int main() {
    // Create and run the thread
    pthread_t thread;
    int data = 100;

    if (pthread_create(&thread, NULL, thread_function, (void *) &data) != 0) {
        printf("Error creating thread.\n");
        return EXIT_FAILURE;
    };

    // Main program output
    printf("I'm the main program.\n");

    return EXIT_SUCCESS;
}