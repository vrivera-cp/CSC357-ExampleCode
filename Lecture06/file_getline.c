#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Please specify a file name.\n");
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");

    char *buffer = NULL;
    size_t count = 0;

    while (getline(&buffer, &count, f) != -1) {
        fputs(buffer, stdout);
    }

    free(buffer);

    fclose(f);

    return 0;
}