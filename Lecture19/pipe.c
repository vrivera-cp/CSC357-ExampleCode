#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define READ_BUFFER_SIZE    32

int main() {
    // Open a pipe
    int fd[2];
    if (pipe(fd) == -1) {
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
        close(fd[1]);

        // Get information from the parent
        char buffer[READ_BUFFER_SIZE];
        int n;
        while ((n = read(fd[0], buffer, READ_BUFFER_SIZE)) != 0) {
            printf("%s", buffer);
        }

        // Cleanup
        close(fd[0]);
    }

    // Parent Logic
    if (pid > 0) {
        // Close "read end" file descriptor
        close(fd[0]);

        // Send a message to the child
        char message[] = "Hello child!\n";
        write(fd[1], message, sizeof(char) * strlen(message));

        // Cleanup
        close(fd[1]);
    }

    return EXIT_SUCCESS;
}