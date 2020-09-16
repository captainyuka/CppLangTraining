#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(){
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c;
    
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        printf("Winsock Failed"); 
        return 1;
    }
    
    if( (s=socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
        printf("Socket Failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
    
    // Bind
    if( bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR )
        printf("Bind failed");
    
    puts("Bind done");
     
    listen(s, 10);

    puts("Waiting for incoming connections\n");
    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, (struct sockaddr*)&client, &c);
    if(new_socket == INVALID_SOCKET)
        printf("accept failed\n");
     
    char* client_ip = inet_ntoa(client.sin_addr);
    int client_port = ntohs(client.sin_port);
    
    printf("Client from %s:%d has connected successfully.", client_ip, client_port);

    closesocket(s);
    WSACleanup();

    return 0;
}


