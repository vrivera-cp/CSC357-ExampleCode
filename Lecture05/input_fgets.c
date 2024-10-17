#include <stdio.h>

int main()
{
    char buffer[100];
    fgets(buffer, 100, stdin);  // Reads up to 99 characters into buffer

    printf("%s", buffer);

    return 0;
}