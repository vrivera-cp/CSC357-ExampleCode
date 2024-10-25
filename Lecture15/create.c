#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

// Checks if a file is a directory or not
int main(int argc, char *argv[]) {
    // Check Argument count
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    // Create the directory
    if (mkdir(argv[1], S_IRWXU | S_IRGRP | S_IROTH | S_ISVTX /*Sticky Bit*/) == -1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}