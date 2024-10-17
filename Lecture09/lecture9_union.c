#include <stdio.h>

int main() {
    union shapeshifter {
        int x;
        float y;
        char *z;
    };

    union shapeshifter s;

    s.x = 100;
    s.y = 200.0;
    s.z = "300";

    printf("%d %f %s\n", s.x, s.y, s.z);
}

