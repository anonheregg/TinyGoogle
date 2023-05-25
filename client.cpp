#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
using namespace std;
int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    //char buffer[1024];
    
    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Set server address properties
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5500);
    serverAddr.sin_addr.s_addr = inet_addr("172.16.4.164");
    

    ifstream  imageFile("twitter.png",ios::binary);
    //size
    imageFile.seekg(0,ios::end);
    int imageSize=imageFile.tellg();
    imageFile.seekg(0,ios::beg);
    //buffer
    char* buffer =new char[imageSize];
    //read
    imageFile.read(buffer,imageSize);
    // Connect to the server
    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    
    // Send data to the server
    //strcpy(buffer, "Hello from client");
    send(clientSocket, buffer, imageSize, 0);
    
    // Receive data from the server
    //memset(buffer, 0, sizeof(buffer));
    //recv(clientSocket, buffer, 1024, 0);
    //std::cout << "Received message from server: " << buffer << std::endl;
    imageFile.close();
    delete[] buffer;
    // Close socket
    close(clientSocket);
    
    return 0;
}
