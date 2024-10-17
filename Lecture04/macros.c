#include <stdio.h>

#define forever for (;;)
#define max(A, B) ((A) > (B) ? (A) : (B))

int main() {
    forever {
        printf("%d\n", max(100, 10));
    }

    return 0;
}
