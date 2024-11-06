/* code taken and adapted from http://www.ecst.csuchico.edu/~beej/guide/net/ */

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

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
