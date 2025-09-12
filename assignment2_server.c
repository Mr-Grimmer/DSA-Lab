#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
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
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }

    // Allow port reuse
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

    // Prepare server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Listen
    if (listen(server_fd, 5) == SOCKET_ERROR) {
        printf("Listen failed\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Server listening on port %d...\n", PORT);

    // Accept client
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd == INVALID_SOCKET) {
        printf("Accept failed\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Client connected.\n");

    // Receive filename
    memset(filename, 0, sizeof(filename));
    recv(client_fd, filename, sizeof(filename), 0);
    printf("Client requested file: %s\n", filename);

    // Open file
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        char *err = "File not found";
        send(client_fd, err, strlen(err), 0);
    } else {
        // Send file contents
        while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
            send(client_fd, buffer, n, 0);
        }
        fclose(fp);
        printf("File transfer complete.\n");
    }

    // Close sockets
    closesocket(client_fd);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}