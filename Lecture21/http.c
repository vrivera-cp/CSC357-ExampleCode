#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define PORT 2828
#define QUEUE_SIZE 50

int create_service(short port) {
    // Create the server's listen socket
    int fd = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM is TCP
    if (fd == -1) {
        return -1;
    }

    // Ensure that the address can be immediately reused after closing the program
    int yes = 1; // Non-zero for indicated to set, rather than unset, the option
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        return -1;
    }

    // Setup our local device IPv4 address for binding
    struct sockaddr_in local_addr; // local device address information
    local_addr.sin_family = AF_INET; // IPv4
    local_addr.sin_port = htons(port); // As a short int in network byte order
    local_addr.sin_addr.s_addr = INADDR_ANY; // Macro for any local device IP, network byte order
    memset(&(local_addr.sin_zero), '\0', 8); // Zero the rest of the struct

    // Bind the socket to our local IP address and port
    if (bind(fd, (struct sockaddr *) &local_addr, sizeof(struct sockaddr)) == -1) {
        return -1;
    }

    // Begin listening for connections
    if (listen(fd, QUEUE_SIZE) == -1) {
        return -1;
    }

    return fd;
}

int accept_connection(int fd) {
    // Setup
    int new_fd;
    struct sockaddr_in remote_addr;
    socklen_t size = sizeof(struct sockaddr_in);

    // Loop, even if accept is interrupted
    errno = EINTR;
    while (errno == EINTR) {
        if ((new_fd = accept(fd, (struct sockaddr*)&remote_addr, &size)) == -1 && errno != EINTR) {
            return -1;
        } else if (new_fd != -1) {
            break;
        }
    }

    return new_fd;
}


void handle_request(int nfd) {
    // Convert socket to a stream
    FILE *network = fdopen(nfd, "r+");
    char *line = NULL;
    size_t size;
    ssize_t num;

    if (network == NULL) {
        perror("fdopen");
        close(nfd);
        return;
    }

    // Read http request
    printf("Received request:\n");
    while ((num = getline(&line, &size, network)) > 0) {
        printf("%s", line);
        if (strcmp(line, "\r\n") == 0) {
            break;
        }
    }

    // Send a response
    char header[] = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n";
    char content[] = "<html><body><p>Hello!</p></body></html>";

    printf("Sending response:\n");
    printf(header, sizeof(content));
    printf("%s", content);
    printf("\n");

    fprintf(network, header, sizeof(content));
    fprintf(network, "%s", content);
    

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
