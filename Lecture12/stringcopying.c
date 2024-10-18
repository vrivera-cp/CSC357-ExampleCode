#include <string.h>
#include <stdlib.h>

int main() {

    char **strings;

    strings = malloc(sizeof(char *) * 3);

    strings[0] = "Mochi";

    strings[1] = malloc(sizeof(char) * 6);

    for (int i = 0; strings[0][i] != '\0'; i++) {
        strings[1][i] = strings[0][i];
    }
    strings[1][5] == '\0';

    strings[2] = strdup(strings[1]);

    free(strings);

    return 0;
}