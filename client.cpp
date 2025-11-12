#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int clientSocket;
    sockaddr_in serverAddr;
    char buffer[1024];

    // Step 1: Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        cout << "Error in connection.\n";
        return 1;
    }
    cout << "Client socket created successfully.\n";

    // Step 2: Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    // Step 3: Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cout << "Connection failed.\n";
        return 1;
    }
    cout << "Connected to server.\n";

    // Step 4: Communication loop
    while (true) {
        cout << "Client: ";
        cin.getline(buffer, 1024);

        send(clientSocket, buffer, strlen(buffer), 0);

        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);
        cout << "Server: " << buffer << endl;
    }

    close(clientSocket);
    return 0;
}
