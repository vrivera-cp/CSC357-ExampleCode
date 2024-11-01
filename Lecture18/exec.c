#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Run the given command
    execvp(argv[1], &argv[1]);

    // Failure
    return EXIT_FAILURE;
}