#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 2828

#define MIN_ARGS 2
#define MAX_ARGS 2
#define SERVER_ARG_IDX 1

#define USAGE_STRING "usage: %s <server address>\n"

void validate_arguments(int argc, char *argv[]) {
    if (argc == 0) {
        fprintf(stderr, USAGE_STRING, "client");
        exit(EXIT_FAILURE);
    }
    else if (argc < MIN_ARGS || argc > MAX_ARGS) {
        fprintf(stderr, USAGE_STRING, argv[0]);
        exit(EXIT_FAILURE);
    }
}

void send_request(int fd) {
    char *line = NULL;
    size_t size;
    ssize_t num;

    while ((num = getline(&line, &size, stdin)) >= 0) {
        write(fd, line, num);
    }

    free(line);
}


int connect_to_server(struct sockaddr *host_address) {
    // Create the socket for communication with the server
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if ((fd) == -1) {
        return -1;
    }

    // Connect the socket to the server
    if (connect(fd, host_address, sizeof(struct sockaddr)) == -1) {
        close(fd);
        perror(0);
        return -1;
    }

    return fd;
}

struct addrinfo *gethost(char *hostname) {
    // Setup our IP address search hint
    struct addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;

    // Convert port to a string
    char port[7]; // Maximum chars is -65534 (6) + \0 (7)
    memset(port, '\0', sizeof(port));
    sprintf(port, "%d", PORT);

    // Obtain potential addresses
    struct addrinfo *addresses = NULL; // Will be a linked list of addresses
    int error_code;
    if ((error_code = getaddrinfo(hostname, port, &hint, &addresses)) != 0) {
        printf("%s", gai_strerror(error_code));
    }

    return addresses;
}

int main(int argc, char *argv[]) {
    validate_arguments(argc, argv);

    // Convert command-line argument to an address
    struct addrinfo *host_address = gethost(argv[SERVER_ARG_IDX]);

    // Connect to the server
    if (host_address) {
        int fd = connect_to_server(host_address->ai_addr); // Use first address
        if (fd != -1) {
            send_request(fd);
            close(fd);
        }
    }

    // Clean up
    freeaddrinfo(host_address);

    return 0;
}
