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
    int clientSocket;
    struct sockaddr_in serverAddr, localAddr;
    char message[BUFFER_SIZE];

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);

    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = INADDR_ANY;
    localAddr.sin_port = htons(0);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    printf("Client socket created\n");

    if (bind(clientSocket, (struct sockaddr *)&localAddr, sizeof(localAddr)) < 0) {
        perror("Bind failed");
        close(clientSocket);
        exit(1);
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        close(clientSocket);
        exit(1);
    }
    printf("Connected to server\n");

    while (1) {
        printf("Enter message: ");
        scanf("%s", message);
        send(clientSocket, message, strlen(message) + 1, 0);
        if (strcmp(message, "quit") == 0) break;
    }

    printf("Disconnected from server\n");
    close(clientSocket);
    return 0;
}
