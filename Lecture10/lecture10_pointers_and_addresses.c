int main() {
    int *p;
    int x = 1, y = 2;
    int z[3] = {3};

    p = &x;
    y = *p;
    *p = 0;
    p = &z[0];
}
