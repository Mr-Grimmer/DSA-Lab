#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>     // <-- Required for socket functions
#include <netinet/in.h>     // For sockaddr_in
#include <arpa/inet.h>      // For inet_ntoa, htons

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    int addrlen = sizeof(address);

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Define address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Accept from any interface
    address.sin_port = htons(PORT);       // Convert to network byte order

    // 3. Bind the socket to IP/Port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // 5. Accept client connection
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to client: %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    // 6. Communication loop
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            printf("Client disconnected or error occurred.\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "quit") == 0) {
            printf("Received 'quit'. Closing connection.\n");
            break;
        }

        const char* response = "Message received\n";
        send(new_socket, response, strlen(response), 0);
    }

    // 7. Close sockets
    close(new_socket);
    close(server_fd);

    return 0;
}