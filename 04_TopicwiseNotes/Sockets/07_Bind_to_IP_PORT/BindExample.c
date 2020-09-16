#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(){
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    
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
    
    closesocket(s);

    return 0;
}


