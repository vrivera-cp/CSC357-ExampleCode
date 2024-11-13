#include <stdio.h>

int one_more_than(int x) {
    return x + 1;
}

double multiply(double x, int y) {
    return x * y;
}

int main(int argc, char* argv[]) {
    int result1, result2;

    int (*my_first_function_pointer)(int);
    my_first_function_pointer = &one_more_than;

    result1 = (*my_first_function_pointer)(100);


    double (*my_second_function_pointer)(double, int) = multiply;

    result2 = my_second_function_pointer(100.0, 2);

    printf("result1: %d\n", result1);
    printf("result2: %d\n", result2);
}