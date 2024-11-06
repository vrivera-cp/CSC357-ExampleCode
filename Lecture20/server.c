#define _GNU_SOURCE
#include "net.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 2828

void handle_request(int nfd) {
    // Convert socket to a stream
    FILE *network = fdopen(nfd, "r");
    char *line = NULL;
    size_t size;
    ssize_t num;

    if (network == NULL) {
        perror("fdopen");
        close(nfd);
        return;
    }

    // Read input until EOF
    while ((num = getline(&line, &size, network)) >= 0) {
        printf("%s", line);
    }

    // Cleanup
    free(line);
    fclose(network);
}

void run_service(int fd) {
    // Continuously accept connections
    while (1) {
        int nfd = accept_connection(fd);
        if (nfd != -1) {
            printf("Connection established\n");
            handle_request(nfd);
            printf("Connection closed\n");
        }
    }
}

int main(void) {
    // Setup Server
    int fd = create_service(PORT);

    if (fd == -1) {
        perror(0);
        exit(1);
    }

    // Start Server
    printf("listening on port: %d\n", PORT);
    run_service(fd);
    close(fd);

    return 0;
}
