#include <stdio.h>

int main() {
    int example1[3];
    int example2[4] = {10};
    int numbers[5] = {10, 20, 30, 40, 50};

    printf("Third: %d\n", numbers[2]);

    numbers[2] = 60;

    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }

    return 0;
}
