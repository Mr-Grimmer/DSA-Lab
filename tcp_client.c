#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>     // For socket functions
#include <netinet/in.h>     // For sockaddr_in
#include <arpa/inet.h>      // For inet_pton

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    // 1. Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Define server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // 3. Connect to the server
    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server. Type messages (type 'quit' to exit):\n");

    // 4. Communication loop
    while (1) {
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send message
        send(sock, buffer, strlen(buffer), 0);

        // Remove newline before checking quit
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strcmp(buffer, "quit") == 0) {
            printf("Exiting client.\n");
            break;
        }

        // Receive response
        memset(buffer, 0, BUFFER_SIZE);
        int valread = recv(sock, buffer, BUFFER_SIZE, 0);
        if (valread <= 0) {
            printf("Server closed connection.\n");
            break;
        }
        printf("Server: %s", buffer);
    }

    // 5. Close the socket
    close(sock);
    return 0;
}