#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Create a child
    pid_t pid = fork();
    if (pid == -1) {
        return EXIT_FAILURE;
    }

    // Child
    if (pid == 0) {
        // Run the given command
        execvp(argv[1], &argv[1]);
        
        // Failure
        return EXIT_FAILURE;
    }

    // Parent
    int wait_status;
    waitpid(pid, &wait_status, 0);
    
    if (WIFEXITED(wait_status)) {
        printf("Good job child! Parent is exiting.\n");
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}