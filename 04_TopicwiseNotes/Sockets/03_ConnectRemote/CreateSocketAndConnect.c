#include <stdio.h>
#include <winsock2.h>


#pragma comment(lib, "ws2_32")

int main(int argc, char** argv){
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;

    printf("\ninit ");
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0){
        printf(" failed\n");
        return 1;
    }

    printf("Socket ");
    if( (s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
        printf(" failed\n");
        return 1;
    }
    
    server.sin_addr.s_addr = inet_addr("185.85.188.58");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if(connect(s, (struct sockaddr*)&server, sizeof(server)) < 0){
        puts("connect error");
        return 1;
    }

    puts("Connected");




return 0;
}
