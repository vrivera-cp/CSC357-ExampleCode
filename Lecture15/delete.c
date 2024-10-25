#include <stdlib.h>
#include <unistd.h>

// Checks if a file is a directory or not
int main(int argc, char *argv[]) {
    // Check Argument count
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    // Delete the directory
    if (rmdir(argv[1]) == -1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}