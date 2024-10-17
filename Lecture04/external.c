#include <stdio.h>
#include "external_shared.c"

extern int shared;

int main() {
    printf("%d\n", shared);
    return 0;
}
