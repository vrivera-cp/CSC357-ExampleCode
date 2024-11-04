#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

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

        // Convert "read end" file descriptor to file stream
        FILE *f = fdopen(fd[0], "r");
        if (f == NULL) {
            close(fd[0]);
            return EXIT_FAILURE;
        }

        // Get information from the parent
        char *buffer = NULL;
        size_t n = 0;
        while ((n = getline(&buffer, &n, f)) != -1) {
            printf("%s", buffer);
        }

        // Cleanup
        free(buffer);
        fclose(f);
    }

    // Parent Logic
    if (pid > 0) {
        // Close "read end" file descriptor
        close(fd[0]);

        // Convert "write end" file descriptor to file stream
        FILE *f = fdopen(fd[1], "w");
        if (f == NULL) {
            close(fd[1]);
            return EXIT_FAILURE;
        }

        // Send a message to the child
        char message[] = "Hello child!\n";
        fprintf(f, "%s", message);

        // Cleanup
        fclose(f);
    }

    return EXIT_SUCCESS;
}