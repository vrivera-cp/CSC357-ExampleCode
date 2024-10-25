#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

// Checks if a file is a directory or not
int main(int argc, char *argv[]) {
    // Check Argument count
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    // Obtain file information
    struct stat sb;
    if (stat(argv[1], &sb) == -1) {
        return EXIT_FAILURE;
    }

    // Check if directory
    if (S_ISDIR(sb.st_mode)) {
        printf("A Directory\n");
    } else {
        printf("Not a Directory\n");
    }

    return EXIT_SUCCESS;
}