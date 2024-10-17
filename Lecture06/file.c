#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Please specify a file name.\n");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");

    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
        fputs(buffer, stdout);
    }

    fclose(f);

    return 0;
}