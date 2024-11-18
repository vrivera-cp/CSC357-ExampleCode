#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_function(void *data) {
    printf("I'm the thread, my data is: %d\n", *((int *) data));
    
    // Create a return value
    int value = *((int *) data) * 2;
    return &value; // Wrong!
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

    // Block until the thread completes execution
    int return_value;
    if (pthread_join(thread, (void *) &return_value) != 0) {
        printf("Error joining thread.\n");
        return EXIT_FAILURE;
    }

    printf("Thread joined. Thread return value is: %d\n", return_value);

    return EXIT_SUCCESS;
}