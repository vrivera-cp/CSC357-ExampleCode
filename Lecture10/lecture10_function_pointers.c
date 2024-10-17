int add(int x, int y) { return x + y; }

int multiply(int x, int y) { return x * y; }

int execute_op(int x, int y, int (*op)(int, int)) {
    return op(x, y);
}

int main() {
    int result;

    int (*operation)(int, int) = &add;
    result = execute_op(1, 2, operation);

    result = execute_op(1, 2, &multiply);

    return 0;
}