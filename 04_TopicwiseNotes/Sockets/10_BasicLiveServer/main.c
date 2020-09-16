#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define TRUE 1
#define FALSE 0
typedef int bool;

void throw_error(char* msg, bool exit_program, int ret_value){
    if(ret_value != -1)
        fprintf(stderr, "%s::WSAErrorCode %d\n", msg, ret_value);
    else{ 
        fprintf(stderr, msg);
        fprintf(stderr, "\n");
    }
    
    // In case any error from WSA comes then cleanup the resources
    if(ret_value >= 0)
        WSACleanup();

    if(exit_program)
        exit(ret_value);
}

int main(){

    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c;
    char* msg;

    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        throw_error("WSAStartup", TRUE, WSAGetLastError());
    
    if( (s=socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
        throw_error("socket", TRUE, WSAGetLastError());

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
    
    if( bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR )
        throw_error("bind", TRUE, WSAGetLastError());
    
    // Listen incoming connections
    listen(s, 10);
    
    puts("Waiting for incoming connections...\n");
    
    c = sizeof(struct sockaddr_in);
    while(new_socket = accept(s, (struct sockaddr*)&client, &c)){
        char* client_ip = inet_ntoa(client.sin_addr);
        int client_port = ntohs(client.sin_port);

        msg = "Hello Client, I have received your connection. I am sorry to say that I need to leave now.d\n";
        send(new_socket, msg, strlen(msg), 0);
    }
    
    closesocket(s);
    WSACleanup();

    return 0;
}
