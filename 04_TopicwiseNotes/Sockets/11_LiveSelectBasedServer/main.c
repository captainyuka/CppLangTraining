#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define TRUE 1
#define FALSE 0

// The following macros planned to be taken as param to main
// That is why we allocate the resources dynamically rather than staticly
#define MAX_NUMBER_OF_CLIENTS 30
#define MAX_RECV_BUFFER_SIZE 1024


/*
 * Throw Error with given msg and also clean the WSA resources before leaving.
 * WSA Error Code is also appeneded appeneded at the end of the msg.
 *
 * @param msg is the msg to output to the stderr
 */
void WsaThrowError(const char* msg){
    fprintf(stderr, "%s:::::WSA Error %d\n", msg, WSAGetLastError());
    WSACleanup(); 
    exit(EXIT_FAILURE);
}

/**
 * Throw Error with given msg and also clean WSA resources and given parameter sockets.
 * If client or server is NULL, no action is done to the NULL param.
 *
 * @param msg is the error msg given to the std err.
 * @param client_sockets is an array of client sockets.
 * @param server is the server socket. when -1 means no need to clean server socket.
 */
void WsaThrowErrorWithCleaningSockets(const char* msg, SOCKET* client_sockets, SOCKET server){ 
    fprintf(stderr, "%s:::::WSA Error %d\n", msg, WSAGetLastError());
    
    while(client_sockets != NULL)               // Traverse the array
        closesocket(*client_sockets++);         // Close the current client socket
    free(client_sockets);                       // Free the dynamically allocated client_sockets array
    
    if( server != -1)
        closesocket(server);                    // Close the ccurent server socket
    WSACleanup();                               // Clean the WSA resources
    exit(EXIT_FAILURE);                         // Exit the program with an error
}


int main(int argc, char** argv){
    
    ///////////////////////////////////////////
    // Declarations
    ///////////////////////////////////////////

    WSADATA wsa;
    SOCKET master, new_socket, *client_socket, s;
    struct sockaddr_in server, address;
    int activity, addrlen, i, valread;
    char* msg = "EACHO Daemon v1.0 \r\n";
    fd_set readfds;                             // Set of file descriptors
    char* buffer;
     
     
    ///////////////////////////////////////////
    // Initializations
    ///////////////////////////////////////////

    client_socket = (SOCKET*)malloc(sizeof(SOCKET) * MAX_NUMBER_OF_CLIENTS);
    buffer = (char*)malloc((MAX_RECV_BUFFER_SIZE+1) * sizeof(char));      // Extra +1 for null termination

    // init all sockets as invalid, later we will put valid ones
    for(i = 0; i < MAX_NUMBER_OF_CLIENTS; ++i)
        client_socket[i] = 0;
    
    // Init the WSA
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        fprintf(stderr, "Failed to startup the WSA:: WSA Error %d\n", WSAGetLastError());
        return EXIT_FAILURE;
    }
    
    // Create socket
    if( (master=socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
        WsaThrowErrorWithCleaningSockets("socket()", client_socket, -1);
    
    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;                // use IPv4
    server.sin_addr.s_addr = INADDR_ANY;        // Anyone can connect
    server.sin_port = htons( 8888 );            // Server will use 8888 port

  
    ///////////////////////////////////////////
    // Bind to the port and listen
    ///////////////////////////////////////////
    
    // Bind server to the specified port
    if( bind(master, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
        WsaThrowErrorWithCleaningSockets("bind()", client_sockets, master);
    
    // Listen to incoming connections
    listen(master, 10);
  
    ///////////////////////////////////////////
    // Accept the client requests and 
    // handle them asynchronously using polling
    // with the help of select()
    ///////////////////////////////////////////
    
    fprintf(stderr, "DEBUG:::::Waiting for incoming connections");

    addrlen = sizeof(struct sockaddr_in);
    while(TRUE){
        // Clear the socket fd set
        FD_ZERO(&readfds);

        // Add the master socket to the fd set
        FD_SET(master, &readfds);
        
        // Add child sockets to the fd set
        for(i=0; i < MAX_NUMBER_OF_CLIENTS; ++i){
            s = client_socket[i];,
            if(s > 0)
                FD_SET(s, &readfds, &readfdss);
        }
            
    }
   
    ///////////////////////////////////////////
    // Cleanup the resources and exit 
    ///////////////////////////////////////////
    
    while(client_socket != NULL)               // Traverse the array
        closesocket(*client_socket++);         // Close the current client socket
    free(client_sockets);                      // Free the dynamically allocated client_sockets array
    
   
    closesocket(master);
    WSACleanup();
    return 0;
}
