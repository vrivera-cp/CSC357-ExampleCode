#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 8
#define THREAD_COUNT 4

int *array1;
int *array2;
int *result;

struct multiply_data {
    int start;
    int end;
};

pthread_t threads[THREAD_COUNT];

void *multiply(void *arg) {
    // Extract arguments for readability
    int start = ((struct multiply_data*) arg)->start;
    int end = ((struct multiply_data*) arg)->end;

    // Perform Multiplication
    for (int i = start; i < end; i++) {
        result[i] = array1[i] * array2[i];
    }

    return NULL;
}

void print_array(char *label, int* array) {
    printf("%s:\t", label);
    for (int i = 0; i < SIZE; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

int main() {
    // Create arrays
    array1 = calloc(SIZE, sizeof(int));
    array2 = calloc(SIZE, sizeof(int));
    result = calloc(SIZE, sizeof(int));

    for (int i = 0; i < SIZE; i++) {
        array1[i] = 1 + i;
        array2[i] = SIZE - i;
    }

    // Print Arrays
    print_array("Array 1", array1);
    print_array("Array 2", array2);

    // Create threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        // Setup Thread Function Arguments
        struct multiply_data thread_data;
        thread_data.start = i * (SIZE / THREAD_COUNT);
        thread_data.end = thread_data.start + SIZE / THREAD_COUNT;
        
        // Create Thread
        pthread_create(&threads[i], NULL, multiply, &thread_data);
    }

    // Join threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print Result
    print_array("Result: ", result);

    return 0;
}