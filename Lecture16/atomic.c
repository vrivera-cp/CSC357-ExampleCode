#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    // Delete file
    unlink("atomic.txt");

    // Open file for appending
    FILE *f;
    if ((f = fopen("atomic.txt", "a")) == NULL) {
        return EXIT_FAILURE;
    }

    // Atomic Writing
    for (int i = 1; i < argc; i++) {
        fprintf(f, "%s\n", argv[i]);
    }

    // Close file
    if (fclose(f) == -1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}