#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET sock_fd;
    struct sockaddr_in server_addr;
    char filename[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    FILE *fp;
    int n;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create TCP socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }

    // Server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Connection failed\n");
        closesocket(sock_fd);
        WSACleanup();
        return 1;
    }

    // Ask for filename
    printf("Enter filename to request: ");
    scanf("%s", filename);

    // Send filename
    send(sock_fd, filename, strlen(filename), 0);

    // Save received file
    fp = fopen("received_file.txt", "wb");
    if (fp == NULL) {
        printf("File create failed\n");
        closesocket(sock_fd);
        WSACleanup();
        return 1;
    }

    // Receive data
    while ((n = recv(sock_fd, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, n, fp);
    }
    fclose(fp);

    printf("File received successfully (saved as 'received_file.txt').\n");

    // Close socket
    closesocket(sock_fd);
    WSACleanup();

    return 0;
}