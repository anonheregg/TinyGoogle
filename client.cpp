#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    //SOCK_STREAM
    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Set server address properties
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5500);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    
    // Connect to the server
    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    
    // Send data to the server
    strcpy(buffer, "i am guhan!");
    send(clientSocket, buffer, strlen(buffer), 0);
    
    // Receive data from the server
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, 1024, 0);
    std::cout << "Received message from server: " << buffer << std::endl;
    
    // Close socket
    close(clientSocket);
    
    return 0;
}
