#include <string.h>
#include <stdlib.h>

int main() {

    char **strings;

    strings = malloc(sizeof(char *) * 3);
    // Initialize allocated values
    for (int i = 0; i < 3; i++) {
        strings[i] = NULL;
    }

    strings[0] = "Mochi";

    strings[1] = malloc(sizeof(char) * 6);
    // Initialize allocated values
    for (int i = 0; i < 6; i++) {
        strings[i] = '\0';
    }

    for (int i = 0; strings[0][i] != '\0'; i++) {
        strings[1][i] = strings[0][i];
    }
    strings[1][5] == '\0';

    strings[2] = strdup(strings[1]);

    free(strings[1]);
    free(strings[2]);
    free(strings);

    return 0;
}