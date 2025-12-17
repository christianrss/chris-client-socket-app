#define _GNU_SOURCE
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *host = "djxmmx.net";
    char *port_str = "17";

    struct addrinfo remote_address;
    struct addrinfo *ptr_remote;
    memset(&remote_address, 0, sizeof(remote_address));
    int gai_result = getaddrinfo(host, port_str, &remote_address, &ptr_remote);
    if (gai_result != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_result));
        return 1;
    }

    // information about the host
    int family = ptr_remote->ai_family;
    int socktype = ptr_remote->ai_socktype;
    int protocol = ptr_remote->ai_protocol;
    struct sockaddr *addr = ptr_remote->ai_addr;
    socklen_t addrlen = ptr_remote->ai_addrlen;

    // defining the socket descriptor
    int sockfd = socket(family, socktype, protocol);

    if (sockfd < 0) {
        perror("socket");
        freeaddrinfo(ptr_remote);
        exit(1);
    } else {
        printf("Socket has been defined.\n");
    }

    // Connecting
    int connected = connect(sockfd, addr, addrlen);

    if (connected < 0) {
        perror("connect");
        close(sockfd);
        freeaddrinfo(ptr_remote);
        exit(1);
    } else {
        printf("Connection has been stablished.\n");
    }

    char buffer[1024];
    size_t bytes;
    while (bytes = recv(sockfd, buffer, sizeof(buffer) -1, 0)) {
        buffer[bytes] = '\0';
        printf("Message from server: %s\n", buffer);
    }

    close(sockfd);
    freeaddrinfo(ptr_remote);

    return 0;
}