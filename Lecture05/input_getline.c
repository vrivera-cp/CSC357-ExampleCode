#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    nread = getline(&line, &len, stdin);

    printf("%s", line);

    return 0;
}