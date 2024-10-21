#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int checked_open(char *pathname, int flags, mode_t mode) {
    int f;
    if ((f = open(pathname, flags, mode)) == -1) {
        fprintf(stderr, "Error opening file %s: %s\n", pathname, strerror(errno));
        return -1;
    }
    return f;
}

int checked_close(int fd) {
    if (close(fd) == -1) {
        perror("Error closing file");
        return -1;
    }
    return 0;
}

char text[] = "Example\nFile\nText\n";
char text_append[] = "More\nExample\nText\n";

int main(int argc, char *argv[]) {
    // Open for writing
    int fw;
    if ((fw = checked_open(argv[1], O_WRONLY | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH)) == -1) return 1;

    write(fw, text, sizeof(text) - 1);

    checked_close(fw);

    // Open for reading
    char *buffer = malloc(sizeof(text));
    int fr;
    if ((fr = checked_open(argv[1], O_RDONLY, 0)) == -1) return 1;
    
    read(fr, buffer, sizeof(text) - 1);
    
    printf("%s", buffer);
  
    free(buffer);
    checked_close(fr);

    // Open for appending
    int fa;
    if ((fa = checked_open(argv[1], O_WRONLY | O_APPEND, 0)) == -1) return 1;
    
    lseek(fa, 0, SEEK_SET); // Seek to start of file

    write(fa, text_append, sizeof(text_append) - 1);
  
    checked_close(fa);

    // Open for reading
    buffer = malloc(sizeof(text_append));
    int fra;
    if ((fra = checked_open(argv[1], O_RDONLY, 0)) == -1) return 1;
    
    lseek(fra, sizeof(text) - 1, SEEK_SET); // Seek to end of first string

    read(fra, buffer, sizeof(text_append) - 1);
    
    printf("%s", buffer);
  
    free(buffer);
    checked_close(fra);

    // Open with truncation
    int ft;
    if ((ft = checked_open(argv[1], O_WRONLY | O_TRUNC, 0)) == -1) return 1;
    checked_close(ft);

    // Print File Descriptors
    printf("fw:\t%d\nfr:\t%d\nfa:\t%d\nfra:\t%d\nft:\t%d\n", fw, fr, fa, fra, ft);

    return 0;
}