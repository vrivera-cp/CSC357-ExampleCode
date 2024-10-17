#include <stdio.h>

void increment(int x) {
    x = x + 1;
}

void modify(int *values) {
    values = 999;
}

int main() {
    // Pass By Value
    int a = 5;

    increment(a);

    printf("%d\n", a); // 5

    // Array Pointer Decay
    int values[3] = {1, 2, 3};

    modify(&a);

    printf("%d\n", values[1]);
}
