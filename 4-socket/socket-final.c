#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define HOST "127.0.0.1"
#define PORT 50000

int main() {
    WSADATA wsaData;
    int iResult;
    
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s == INVALID_SOCKET) {
        printf("Invalid socket\n");
        return 1;
    }

    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(HOST);
    clientService.sin_port = htons(PORT);

    iResult = connect(s, (SOCKADDR *)&clientService, sizeof(clientService));
    if(iResult == SOCKET_ERROR) {
        printf("Failed to connect\n");
        return 1;
    }

    printf("Connected!\n");

    const char *buffer = "Hello world!";
    iResult = send(s, buffer, sizeof(char) * strlen(buffer), 0);

    printf("String '%s' sent (%d bytes)\n", buffer, iResult);

    iResult = shutdown(s, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("Failed to shutdown\n");
        return 1;
    }

    printf("Receiving: '");
    do {
        char recvbuffer[64];

        iResult = recv(s, recvbuffer, sizeof(recvbuffer), MSG_WAITALL);
        if(iResult > 0) {
            fwrite(recvbuffer, sizeof(char), iResult, stdout);
        }
    }
    while(iResult > 0);
    printf("'\n");

    iResult = closesocket(s);
    if (iResult == SOCKET_ERROR) {
        printf("Failed to close\n");
        return 1;
    }

    return 0;
}
