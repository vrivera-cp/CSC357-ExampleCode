#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <sys/wait.h>

int main() {
    // Fork into a this process and a second duplicate process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    int wait_status;
    if (pid == 0) { // Child
        sleep(5); // Delay for 5 seconds
        printf("I am the child!\n");
        exit(EXIT_SUCCESS);
    }
    
    // Parent
    printf("I am the parent. My child's PID is %d.\n", pid);
    waitpid(pid, &wait_status, 0); // Wait for the child to terminate
    
    // Check if the child exited properly
    if (WIFEXITED(wait_status)) {
        printf("Let's go, child.\n");
    } else {
        printf("Something bad happened to the child...\n");
    }

    exit(EXIT_SUCCESS);
}