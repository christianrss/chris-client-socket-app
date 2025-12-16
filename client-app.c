#define _GNU_SOURCE
#include <stdio.h>
#include <netdb.h>
#include <string.h>

int main() {
    char *host = "sharpex.com.br";
    char *port_str = "80";

    struct addrinfo remote_address;
    struct addrinfo *ptr_remote;
    memset(&remote_address, 0, sizeof(remote_address));
    int gai_result = getaddrinfo(host, port_str, &remote_address, &ptr_remote);
    if (gai_result != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_result));
        return 1;
    }

    printf("C client!\n");
    return 0;
}