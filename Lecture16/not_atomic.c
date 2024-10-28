#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    FILE *f;
    if ((f = fopen("not_atomic.txt", "w")) == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        fseek(f, 0, SEEK_END);
        fprintf(f, "%s\n", argv[i]);
    }

    if (fclose(f) == -1) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}