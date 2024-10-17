#include <stdio.h>

void increment() {
    static int x = 0;
    printf("%d\n", x);
    x++;
}

int main() {
    for (int i = 0; i < 5; i++) {
        increment();
    }
}
