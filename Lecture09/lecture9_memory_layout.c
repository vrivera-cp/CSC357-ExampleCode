#include <stdio.h>


int main() {
    struct person {
        int birth_year;
        char first_initial;
        int age;
    };

    struct person p;

    printf("sizeof(int):\t%ld\n", sizeof(int));
    printf("sizeof(char):\t%ld\n", sizeof(char));
    printf("sizeof(p)\t%ld\n", sizeof(p));

    return 0;
}
