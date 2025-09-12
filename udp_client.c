#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in servaddr;
    int len, n;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }

    // Server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(servaddr);

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // remove newline

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, len);

        n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&servaddr, &len);
        if (n > 0) {
            buffer[n] = '\0';
            printf("Server: %s\n", buffer);
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}