#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
using namespace std;
//SOCK_DGRAM
int main(){
    char buffer[1024];
    int serverSocket ,portnum,clientLen,newSocket;
    struct sockaddr_in serverAddr,clientAddr;
    serverSocket=socket(AF_INET,SOCK_STREAM,0);
    //server prop
    
    portnum=4502;
    serverAddr.sin_family= AF_INET;
    serverAddr.sin_port= htons(portnum);
    serverAddr.sin_addr.s_addr=INADDR_ANY;

    //bind
    bind(serverSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    //
    listen(serverSocket,5);
    cout<<"server started:"<<portnum<<"\n";

    //client request is proceed
    clientLen=sizeof(clientAddr);
    newSocket=accept(serverSocket,(struct sockaddr *)&clientAddr,(socklen_t*)&clientLen);
    //

    recv(newSocket,buffer,1024,0);
    cout<<"message:"<<buffer<<"\n";
    send(newSocket,"guhhji",strlen("guhhji"),0);
   //close
   close(newSocket);
   close(serverSocket);
   return 0;


}
