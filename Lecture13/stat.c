#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

#define TIME_STRING_BUFFER_SIZE 128

int main(int argc, char *argv[]) {
    struct stat meta_data; 

    if (stat(argv[1], &meta_data) == -1) {
        perror("Error stating file:");
        return 1;
    }

    printf("User ID:\t%d\n", meta_data.st_uid);
    printf("Group ID:\t%d\n", meta_data.st_gid);
    printf("Size:\t\t%ld\n", meta_data.st_size);

    char time_string[TIME_STRING_BUFFER_SIZE];
    struct tm * timeinfo = localtime(&meta_data.st_mtime);
    strftime(time_string, TIME_STRING_BUFFER_SIZE, "Date and Time:\t%Y-%m-%d %H:%M:%S", timeinfo);
    printf("%s\n", time_string);

    return 0;
}