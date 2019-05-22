#ifndef INCLUDE_SOCKET_LIB
#define INCLUDE_SOCKET_LIB 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    /* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0501
    #endif
    #include <winsock2.h>
    #include <Ws2tcpip.h>

    #define SOCKET_T SOCKET
#else
    /* Assume that any non-Windows platform uses POSIX-style sockets instead */
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>

    #define SOCKET_T int
#endif

int socket_init() {
    #ifdef _WIN32
        WSADATA wsa_data;
        return WSAStartup(MAKEWORD(2, 2), &wsa_data);
    #else
        return 0;
    #endif
}

int socket_quit() {
    #ifdef _WIN32
        return WSACleanup();
    #else
        return 0;
    #endif
}

SOCKET_T socket_create() {
    #ifdef _WIN32
        SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(s == INVALID_SOCKET) {
            return 0;
        }
        return s;
    #else
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0) {
            return 0;
        }
        return sock;
    #endif
}

int socket_connect(SOCKET_T socket, const char *hostname, int port) {
    #ifdef _WIN32
        char port_str[128];
        memset(port_str, 0, sizeof(char) * 128);
        sprintf(port_str, "%d", port);

        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        struct addrinfo *result = NULL;

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        if(getaddrinfo(hostname, port_str, &hints, &result) != 0) {
            return -1;
        }

        struct addrinfo *ptr = NULL;
        for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
            if(ptr->ai_family == AF_INET && ptr->ai_socktype == SOCK_STREAM) {
                if(connect(socket, ptr->ai_addr, ptr->ai_addrlen) == SOCKET_ERROR) {
                    return -1;
                }
                else {
                    return 0;
                }
            }
        }

        return -1;
    #else
        struct hostent *server = gethostbyname(hostname);
        if(server == NULL) {
            return -1;
        }

        char server_ip_str[server->h_length];
        inet_ntop(AF_INET, server->h_addr, server_ip_str, server->h_length);

        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

        if(connect(socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            return -1;
        }
    #endif

    return 0;
}

int socket_bind(SOCKET_T socket, const char *hostname, int port) {
    #ifdef _WIN32
        char port_str[128];
        memset(port_str, 0, sizeof(char) * 128);
        sprintf(port_str, "%d", port);

        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        struct addrinfo *result = NULL;

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        if(getaddrinfo(hostname, port_str, &hints, &result) != 0) {
            return -1;
        }

        struct addrinfo *ptr = NULL;
        for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
            if(ptr->ai_family == AF_INET && ptr->ai_socktype == SOCK_STREAM) {
                if(bind(socket, ptr->ai_addr, ptr->ai_addrlen) == SOCKET_ERROR) {
                    return -1;
                }
                else {
                    return 0;
                }
            }
        }

        return -1;
    #else
        struct hostent *server = gethostbyname(hostname);
        if(server == NULL) {
            return -1;
        }

        char server_ip_str[server->h_length];
        inet_ntop(AF_INET, server->h_addr, server_ip_str, server->h_length);

        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

        if(bind(socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            return -1;
        }
    #endif

    return 0;
}

int socket_listen(SOCKET_T socket) {
    #ifdef _WIN32
        return (listen(socket, SOMAXCONN) == 0) ? 0 : -1;
    #else
        return (listen(socket, 128) == 0) ? 0 : -1;
    #endif
}

SOCKET_T socket_accept(SOCKET_T socket) {
    #ifdef _WIN32
        SOCKET s = accept(socket, NULL, NULL);
        if(s == INVALID_SOCKET) {
            return 0;
        }
        return s;
    #else
        int s = accept(socket, NULL, NULL);
        if(s < 0) {
            return 0;
        }
        return s;
    #endif
}

void socket_close_send(SOCKET_T socket) {
    #ifdef _WIN32
        shutdown(socket, SD_SEND);
    #else
        shutdown(socket, SHUT_WR);
    #endif
}

void socket_close_receive(SOCKET_T socket) {
    #ifdef _WIN32
        shutdown(socket, SD_RECEIVE);
    #else
        shutdown(socket, SHUT_RD);
    #endif
}

int socket_close(SOCKET_T socket) {
    #ifdef _WIN32
        if(closesocket(socket) == SOCKET_ERROR) {
            return -1;
        }
        return 0;
    #else
        return close(socket);
    #endif
}

int socket_read_all(SOCKET_T socket, char *buffer, int buffer_len) {
    memset(buffer, 0, buffer_len);

    int read = 0, cum_read = 0;
    while((read = recv(socket, buffer + cum_read, buffer_len - cum_read, 0)) > 0) {
        cum_read += read;
    }

    return cum_read;
}

#endif
