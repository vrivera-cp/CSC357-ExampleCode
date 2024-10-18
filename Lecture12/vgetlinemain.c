#include <stdio.h>
#include <stdlib.h>

#include "vgetline.h"

int main(int argc, char *argv[]) {
    char *buffer = NULL;
    int buffer_size;

    while (vgetline(&buffer, &buffer_size, stdin) != -1) {
        printf("[%d] %s", buffer_size, buffer);
    }

    free(buffer);

    return 0;
}