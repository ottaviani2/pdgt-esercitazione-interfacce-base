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

    // Put code here!

    return 0;
}
