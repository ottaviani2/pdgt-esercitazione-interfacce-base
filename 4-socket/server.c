#include <stdio.h>
#include "socket-lib.h"

#define HOST "127.0.0.1"
#define PORT 1234

int main() {
    if(socket_init() != 0) {
        fprintf(stderr, "Socket initialization failed\n");
        return 1;
    }

    SOCKET_T socket = socket_create();
    if(socket == 0) {
        fprintf(stderr, "Failed to create socket\n");
        return 1;
    }

    if(socket_bind(socket, HOST, PORT) < 0) {
        fprintf(stderr, "Failed to bind socket to %s:%d\n", HOST, PORT);
        return 1;
    }

    printf("Socket bound to %s:%d\n", HOST, PORT);

    if(socket_listen(socket) < 0) {
        fprintf(stderr, "Failed to listen\n");
        return 1;
    }

    printf("Waiting for incoming connections...\n");
    while(1) {
        SOCKET_T incoming = socket_accept(socket);
        if(incoming == 0) {
            fprintf(stderr, "Could not accept connection\n");
            break;
        }

        printf("Connected!\n");

        // Socket open, put code here!

        // Sample functions (see socket-lib.h):
        // socket_read_all(socket, buffer, buffer_size);
        // send(socket, buffer, buffer_size, 0);

        char buffer[512];
        int read = socket_read_all(incoming, buffer, 512);
        send(incoming, buffer, read, 0);
        
        socket_close(incoming);

    }

    if(socket_quit(socket) != 0) {
        fprintf(stderr, "Socket finalization failed\n");
        return 1;
    }

    return 0;
}
