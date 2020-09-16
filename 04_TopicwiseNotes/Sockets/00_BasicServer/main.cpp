#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_MEAN 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

void throw_error(const char* err_msg){
	fprintf(stderr, err_msg);
	printf("\tWSA Error Code %d", WSAGetLastError());
	WSACleanup();
	exit(1);
}

int __cdecl main(void){
    
    /////////////////////////////
    // Var Declarations
    /////////////////////////////

    WSADATA wsa_data;                       // Windows Socket Address Data
    int init_result;                        // Store results when init something

    SOCKET listen_socket = INVALID_SOCKET;  // Server Socket
    SOCKET client_socket = INVALID_SOCKET; 

    struct addrinfo* result = NULL;         
    struct addrinfo hints;

    char recvbuf[DEFAULT_BUFLEN];           // buffer for data received
    int send_result;                        
    int recv_buf_len;                       
   
    /////////////////////////////
    // Initialize winsock 
    /////////////////////////////
     
    init_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if(init_result != 0){
        printf("WSAStartup failed with error: %d\n", init_result);
        return 1;
    }
    
    /////////////////////////////
    // Prepare the socket info
    /////////////////////////////
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;                 // Use IPv4 
    hints.ai_socktype = SOCK_STREAM;           // Use Connection rather than datagram
    hints.ai_protocol = IPPROTO_TCP;           // Use TCP Protocol

    // Let this socket be suitable for bind(), and can accept() connections.
    hints.ai_flags = AI_PASSIVE;                

    init_result = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if( init_result != 0 )
        throw_error("getaddrinfo");  
     
    /////////////////////////////
    // Bind to the socket and accept connections 
    /////////////////////////////
    
    listen_socket = socket(result->ai_family,
                          result->ai_socktype,
                          result->ai_protocol);
    if( listen_socket == INVALID_SOCKET ){
        freeaddrinfo(result);
        throw_error("socket");
    }

    init_result = bind(listen_socket, result->ai_addr, (int)result->ai_addrlen);
    if( init_result == SOCKET_ERROR){
        freeaddrinfo(result);
        closesocket(listen_socket);
        throw_error("bind");
    } 

    client_socket = accept(listen_socket, NULL, NULL);
    if( client_socket == INVALID_SOCKET){
        closesocket(listen_socket);
        throw_error("accept");
    }
    
    /////////////////////////////
    // Data Exchange 
    /////////////////////////////
    
    closesocket(listen_socket);                 // no longer need server socket
    
    do{
        init_result = recv(client_socket, recvbuf, recv_buf_len, 0);

        if( init_result > 0 ){
            printf("Bytes received: &d\n", init_result);

            // Echo the buffer back to the sender
            send_result = send(client_socket, recvbuf, init_result, 0);
            if( send_result == SOCKET_ERROR ){
                closesocket(client_socket);
                throw_error("send");
            }

            printf("Bytes sent: %d\n");
        }else if( init_result == 0)
            printf("Connection closing...\n");
        else{
            closesocket(client_socket);
            throw_error("recv");
        }

    }while(init_result > 0);
    
    
    /////////////////////////////
    // Clean Up Resources
    /////////////////////////////
    
    // Shutdown the connection since no longer needed
    init_result = shutdown(client_socket, SD_SEND);
    if( init_result == SOCKET_ERROR ){
        closesocket(client_socket);
        throw_error("shutdown");
    }   

    closesocket(client_socket);
    WSACleanup();

return 0;
}
