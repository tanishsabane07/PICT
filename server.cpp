#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;
    char buffer[1024];

    // Step 1: Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cout << "Error in connection.\n";
        return 1;
    }
    cout << "Server socket created successfully.\n";

    // Step 2: Configure settings of the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Port number
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP

    // Step 3: Bind the socket
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Error in binding.\n";
        return 1;
    }
    cout << "Bind successful.\n";

    // Step 4: Listen for connections
    if (listen(serverSocket, 5) == 0)
        cout << "Listening...\n";
    else {
        cout << "Error in listening.\n";
        return 1;
    }

    // Step 5: Accept a connection
    addr_size = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &addr_size);
    cout << "Client connected.\n";

    // Step 6: Communication loop
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;

        cout << "Client: " << buffer << endl;

        // Echo the same message back
        send(clientSocket, buffer, strlen(buffer), 0);
    }

    cout << "Connection closed.\n";
    close(clientSocket);
    close(serverSocket);
    return 0;
}
