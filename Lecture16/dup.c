#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define PROCESS_1       0
#define PROCESS_2       1
#define PROCESS_COUNT   2

#define INSTRUCTION_SEEK    0
#define INSTRUCTION_WRITE   1
#define INSTRUCTION_COUNT   2

int main(int argc, char *argv[]) {
    // Setup for emulated "multi-process" writing
    int f[PROCESS_COUNT];

    // Open a single file
    f[PROCESS_1] = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

    if (f[PROCESS_1] == -1) {
        return EXIT_FAILURE;
    }

    // Duplicate the file descriptor for the "second" process
    f[PROCESS_2] = dup(f[PROCESS_1]); // Similar to dup2(p[PROCESS_1], 4)

    // Setup for "multi-process" file writing
    int i[PROCESS_COUNT] = {3, 3}; // Start at argv[3]
    long seek[PROCESS_COUNT];
    int instruction[PROCESS_COUNT] = {INSTRUCTION_SEEK, INSTRUCTION_SEEK};

    // Setup Random Seed
    srand(time(NULL));

    // Perform "multi-process" writing
    while (i[PROCESS_1] < argc && i[PROCESS_2] < argc) {
        // Randomly select a process
        int process;
        if (i[PROCESS_1] == argc) {
            process = PROCESS_2;
        } else if (i[PROCESS_2] == argc) {
            process = PROCESS_1;
        } else {
            process = random() % PROCESS_COUNT;
        }

        // Perform the next instruction
        switch (instruction[process]) {
            case INSTRUCTION_SEEK:
                lseek(f[process], 0, SEEK_END);
            break;
            case INSTRUCTION_WRITE:
                // Retrieve text
                int len = strlen(argv[i[process]]) + 1;
                char line[len];
                strcpy(line, argv[i[process]]);

                // Replace string terminal with newline character
                line[len - 1] = '\n';

                // Write the line
                write(f[process], line, sizeof(char) * len);
            break;
        }

        // Update to the next instruction
        instruction[process]++;

        // Update to next index, if done with one iteration
        if (instruction[process] == INSTRUCTION_COUNT) {
            i[process]++;
            instruction[process] = 0; // Return to first instruction
        }
    }

    // Cleanup
    if (close(f[PROCESS_1]) == -1) {
        return EXIT_FAILURE;
    }

    return 0;
}