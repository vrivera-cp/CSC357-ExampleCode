#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Print the absolute path of the current directory
int main() {
    char working_directory[PATH_MAX];
    getcwd(working_directory, PATH_MAX);
    printf("%s\n", working_directory);

    return EXIT_SUCCESS;
}