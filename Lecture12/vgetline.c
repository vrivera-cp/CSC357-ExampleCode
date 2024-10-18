#include <stdio.h>
#include <stdlib.h>

#include "vgetline.h"

int vgetline(char **buffer, int *n, FILE *f) {
    // Allocate initial space, if necessary
    if (*buffer == NULL) {
        *n = GETLINE_CAPACITY_DEFAULT;
        *buffer = malloc(sizeof(char)*(*n));
        if (*buffer == NULL) {
            return -1; // Allocation failed
        }
    }

    // Iterate over line character-by-character
    int i = 0;
    char current;
    while ((current = getc(f)) != EOF) {
        // Ensure Buffer is large enough for current character plus terminator
        if (i + 1 >= *n) {
            *n *= GETLINE_CAPACITY_INCREASE;
            *buffer = realloc(*buffer, sizeof(char) * (*n));
            if (*buffer == NULL) {
                return -1; // Allocation failed
            }
        }

        // Copy to Buffer
        (*buffer)[i++] = current;

        // Stop at newlines
        if (current == '\n') {
            break;
        }
    }

    // No input and EOF reached
    if (i == 0 && current == EOF) {
        return -1;
    }

    // Insert terminator
    (*buffer)[i] = '\0';

    return i;
}