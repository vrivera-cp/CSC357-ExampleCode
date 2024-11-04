#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define READ_BUFFER_SIZE    32

int main() {
    // Open two pipe
    int pipe1[2];
    if (pipe(pipe1) == -1) {
        return EXIT_FAILURE;
    }

    int pipe2[2];
    if (pipe(pipe2) == -1) {
        return EXIT_FAILURE;
    }

    // Create a child
    pid_t pid = fork();
    if (pid == -1) {
        return EXIT_FAILURE;
    }

    // Child Logic
    if (pid == 0) {
        // Close "write end" file descriptor
        close(pipe1[1]);
        
        // Close "read end" file descriptor
        close(pipe2[0]);

        // Get information from the parent
        char buffer[READ_BUFFER_SIZE];
        int n;
        while ((n = read(pipe1[0], buffer, READ_BUFFER_SIZE)) > 0) {
            printf("%s", buffer);
        }
        
        // Cleanup
        close(pipe1[0]);

        // Send a message to the parent
        char message[] = "Hello parent!\n";
        write(pipe2[1], message, sizeof(char) * strlen(message));

        // Cleanup
        close(pipe2[1]);
    }

    // Parent Logic
    if (pid > 0) {
        // Close "read end" file descriptor
        close(pipe1[0]);

        // Close "write end" file descriptor
        close(pipe2[1]);

        // Send a message to the child
        char message[] = "Hello child!\n";
        write(pipe1[1], message, sizeof(char) * strlen(message));

        // Cleanup
        close(pipe1[1]);

        // Get information from the child
        char buffer[READ_BUFFER_SIZE];
        int n;
        while ((n = read(pipe2[0], buffer, READ_BUFFER_SIZE)) > 0) {
            printf("%s", buffer);
        }
        
        // Cleanup
        close(pipe2[0]);
    }

    return EXIT_SUCCESS;
}