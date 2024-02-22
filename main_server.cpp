// main_server.cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// Constants for server configuration
const int PORT = 8080;
const int MAX_CONNECTIONS = 100;

int main() {
    // Initialize the server
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating server socket." << std::endl;
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding server socket." << std::endl;
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, MAX_CONNECTIONS) == -1) {
        std::cerr << "Error listening on server socket." << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Distributed Server is running on port " << PORT << "..." << std::endl;

    // Handle incoming requests - Placeholder code
    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            std::cerr << "Error accepting client connection." << std::endl;
            continue;
        }

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead == -1) {
            std::cerr << "Error reading from client." << std::endl;
            close(clientSocket);
            continue;
        }

        // Process incoming requests
        std::cout << "Received message from client: " << buffer << std::endl;

        // Respond to requests
        const char* response = "Hello from the server!";
        send(clientSocket, response, strlen(response), 0);

        close(clientSocket);
    }

    // Cleanup and close server socket
    close(serverSocket);

    return 0;
}
