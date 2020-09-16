#include <stdio.h>
#include <winsock2.h>


#pragma comment(lib, "ws2_32")

int main(int argc, char** argv){
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char* msg;
    char server_reply[2000];
    int recv_size;

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
    
    server.sin_addr.s_addr = inet_addr("216.58.206.174");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    
    // connect to a remote server
    if(connect(s, (struct sockaddr*)&server, sizeof(server)) < 0){
        puts("connect error");
        return 1;
    }

    // send some data
    msg = "GET / HTTP/1.1\r\n\r\n";
    if(send(s, msg, strlen(msg), 0) < 0){
        puts("Send failed");
        return 1;
    }

    puts("Data sent\n");

    // Receive a reply from the server
    if( (recv_size = recv(s, server_reply, 2000, 0)) == SOCKET_ERROR )
        puts("recv failed");
    else
        puts("reply received");
    
    // Add a NULL termination to read string
    server_reply[recv_size] = '\0';
    
    puts(server_reply);

return 0;
}
