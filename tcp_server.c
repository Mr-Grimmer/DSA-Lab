#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 100
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 1500

int main() {
    int serverSocket, clientSocket, receivedBytes;
    socklen_t clientAddrLen;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    printf("Server socket created\n");

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        exit(1);
    }
    printf("Bind successful\n");

    listen(serverSocket, 5);
    printf("Server listening on port %d\n", SERVER_PORT);

    while (1) {
        clientAddrLen = sizeof(clientAddr);
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client connected [IP %s, Port %d]\n",
               inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        while (1) {
            memset(buffer, 0, BUFFER_SIZE);
            receivedBytes = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if (receivedBytes <= 0) break;
            printf("Message from [IP %s, Port %d]: %s\n",
                   inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buffer);
            if (strcmp(buffer, "quit") == 0) break;
        }

        printf("Closing connection with [IP %s, Port %d]\n",
               inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}
