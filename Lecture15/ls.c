#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

// Print all files in a directory
int main(int argc, char *argv[]) {
    // Check Argument count
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    // Open directory
    DIR *d;
    if ((d = opendir(argv[1])) == NULL) {
        return EXIT_FAILURE;
    }

    // Iterate over the directory
    struct dirent *inode_name_pair;
    while ((inode_name_pair = readdir(d)) != NULL) {
        printf("%ld %s\n", inode_name_pair->d_ino, inode_name_pair->d_name);
    }

    // Cleanup
    if (closedir(d) == -1) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}