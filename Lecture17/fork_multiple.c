#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define CHILD_COUNT    4
#define randrange(X, Y) (X + (random() % (Y - X)))

void process_child(int pid, int time) {
    sleep(time);
}

void process_parent() {
    pid_t child_pid;
    
    // Repeatedly wait for children to wake
    // This loop occurs whenever a child terminates
    while ((child_pid = wait(NULL)) != -1) {
        printf("Child %d has awoken.\n", child_pid);
    }

    printf("All children have woken!\n");
}

int main() {

    for (int i = 0; i < CHILD_COUNT; i++) {
        // Generate a random sleep for each child
        // Why can't this be done in the child?
        int sleep_time = randrange(1, 8);
        int pid = fork();
        
        if (pid == 0) {
            // Perform child logic
            process_child(pid, sleep_time);

            // Ensure children don't run the rest of the program
            exit(EXIT_SUCCESS);
        } else {
            // Perform parent logic
            printf("Spawned child %d\n", pid);
        }
    }

    process_parent();

    return EXIT_SUCCESS;
}