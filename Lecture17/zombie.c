#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>

int main() {
    // Fork into a this process and a second duplicate process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // This process is the child
        printf("I am the child! My parent's PID is %d. My PID is %d\n", getppid(), getpid());
    } else { // This process is the parent
        sleep(10);
        printf("I am the parent. My child's PID is %d.\n", pid);
    }

    exit(EXIT_SUCCESS);
}