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

void DisconnectTheClient(struct sockaddr_in address, SOCKET s, SOCKET* client_socket){
    // Check if somebody disconnected unexpectedly
    int error_code = WSAGetLastError();
    if(error_code == WSAECONNRESET){
       fprintf(stderr, "Host disconnected unexpectedly:::IP = %s:::PORT = %d\n",
               inet_ntoa(address.sin_addr),
               ntohs(address.sin_port)); 
       closesocket(s);
       client_socket[i] = 0
    }else
       fprintf(stderr, "recv failed with error code: %d", error_code);
}

void init(WSADATA* wsa_ptr, SOCKET* client_socket, int max_number_of_clients, int max_recv_buff_size){
    int i;
    client_socket = (SOCKET*)malloc(sizeof(SOCKET) * max_number_of_clients);
    buffer = (char*)malloc((max_recv_buffer_size+1) * sizeof(char));      // Extra +1 for null termination

    // init all sockets as invalid, later we will put valid ones
    for(i = 0; i <max_number_of_clients; ++i)
        client_socket[i] = 0;
    
    // Init the WSA
    if(WSAStartup(MAKEWORD(2, 2), wsa_ptr) != 0){
        fprintf(stderr, "Failed to startup the WSA:: WSA Error %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    
    return &wsa;
} 

SOCKET SetupTheServer(int port, struct sockaddr_in* server, SOCKET* client_socket){  
    // Create socket
    if( (master=socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
        WsaThrowErrorWithCleaningSockets("socket()", client_socket, -1);

    // Prepare the sockaddr_in structure
    server->sin_family = AF_INET;                // use IPv4
    server->sin_addr.s_addr = INADDR_ANY;        // Anyone can connect
    server->sin_port = htons( 8888 );            // Server will use 8888 port
    
    return master;
}

void StartTheServer(SOCKET master, int max_wait_queue_size, struct sockaddr_in server, SOCKET* client_socket){
    // Bind server to the specified port
    if( bind(master, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
        WsaThrowErrorWithCleaningSockets("bind()", client_socket, master);
    
    // Listen to incoming connections
    listen(master, max_wait_queue_size); 
}

void SetupTheFdSet(SOCKET master, fd_set* readfds_ptr, SOCKET* client_socket){ 
    SOCKET s;
    int i;

    // Clear the socket fd set
    FD_ZERO(readfds);

    // Add the master socket to the fd set
    FD_SET(master, readfds);
    
    // Add child sockets to the fd set
    for(i=0; i < MAX_NUMBER_OF_CLIENTS; ++i)
        if((s=client_socket[i]) > 0)
            FD_SET(s, readfds);
} 

void HandleServerMaster(SOCKET master, struct sockaddr_in address,const char* msg){
    SOCKET new_socket;
    int addrlen = sizeof(struct sockaddr_in);

    if((new_socket = accept(master, (struct sockaddr*)&address, (int*)&addrlen)) < 0)
        WsaThrowErrorWithCleaningSockets("Select()", client_socket, master);

    printf("New Sconnection:::Socket fd = %d:::IP = %d:::PORT = %d\n",
            new_socket,
            inet_ntoa(address.sin_addr),
            ntohs(address.sin_port));

    // Send new connection greeting message
    if(send(new_socket, msg, strlen(msg), 0) != strlen(msg))
        fprintf(stderr, "Msg Sending Failed\n");
    else
        fprintf(stderr, "DEBUG::::: Msg Has been sent successfully\n");
    
    // Add the new socket to the array of sockets
    for(i = 0; i < max_clients; ++i)
        if(client_socket[i] == 0){
            client_socket[i] = new_socket;
            fprintf(stderr, "DEBUG:::::Adding socket to the list of sockets at index %d\n", i);
            break;
        } 
}

// Otherwise the ther exists some IO operation on one of the client sockets
// which means one of the clients has sent a request
void HandleServerClient(SOCKET* client_socket, struct addr_in address, char* buffer){
    SOCKET s;
    int valread;
    int addrlen = sizeof(address);
    

    for(i, = 0; i < MAX_NUMBER_OF_CLIENTS; ++i)
        if(FD_ISSET((s=client_socket[i]), &readfds)){
            // Get details of the client
            getpeername(s, (struct sockaddr*)&address, (int*)&addrlen);

            // Check if it was for closing
            // and also read the incoming msg
            // do not forget, recv doeos not place a null at the end of str
            valread = recv(s, buffer, MAX_RECV_BUFFER_SIZE);

            if(valread == SOCKET_ERROR)
                DisconnectTheClient(address, s, client_socket);
            else if(valread == 0){
                // Somebody disconnected, print the client's details
                printf("Host disconnected:::IP = %s, PORT = %d\n", 
                        inet_ntoa(address.sin_addr), 
                        ntohs(address.sin_port) );
                // Close the socket and mark as 0 in the client list for reuse
                closesocket(s);
                client_socket[i] = 0;
            }else{
                // Echo back the msg that came in  
                buffer[valread] = '\0';
                printf("%s:%d - %s\n", inet_ntoa(address.sin_addr),
                                       ntohs(address.sin_port),
                                       buffer);
                send(s, buffer, valread, 0)
            }
        }
}

void CleanResources(SOCKET master, SOCKET* client_socket){

    while(client_socket != NULL)               // Traverse the array
        closesocket(*client_socket++);         // Close the current client socket
    free(client_socket);                      // Free the dynamically allocated client_sockets array
    
   
    closesocket(master);
    WSACleanup(); 
}

/*
 * Throw Error with given msg and also clean the WSA resources before leaving.
 * WSA Error Code is also appeneded at the end of the msg.
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
    
    if( server != -1 )
        closesocket(server);                    // Close the ccurent server socket
    WSACleanup();                               // Clean the WSA resources
    exit(EXIT_FAILURE);                         // Exit the program with an error
}


int main(int argc, char** argv){
    
    ///////////////////////////////////////////
    // Declarations
    ///////////////////////////////////////////

    WSADATA wsa;                                // Windows Socket A. Data
    SOCKET master;
    SOCKET new_socket
    SOCKET* client_socket
    SOCKET s;
    struct sockaddr_in server;
    struct sockaddr_in address;
    int activity;
    int i;
    int valread;
    char* msg = "EACHO Daemon v1.0 \r\n";
    char* buffer;
    fd_set readfds;                             // Set of file descriptors
     
     
    ///////////////////////////////////////////
    // Initializations
    ///////////////////////////////////////////
    
    init(&wsa, client_socket, MAX_NUMBER_OF_CLIENTS, MAX_RECV_BUFF_SIZE);
    
    // Sets up the server and returns the server master
    master = SetupTheServer(8888, &server, client_socket);  

    ///////////////////////////////////////////
    // Bind to the port and listen
    ///////////////////////////////////////////
    
    // Start the server with a wait queue size of 10 
    StartTheServer(master, 10, server, client_socket);
  
    ///////////////////////////////////////////
    // Accept the client requests and 
    // handle them asynchronously using polling
    // with the help of select()
    ///////////////////////////////////////////
    
    fprintf(stderr, "DEBUG:::::Waiting for incoming connections");

    while(TRUE){ 
        // Setup the File Descriptor Set for select function()
        SetupTheFdSet(master, &readfds_ptr, client_socket);
        
        // Wait for an activity on any of the sockets
        // timeout is NULL, which means we wait indefinitely
        activity = select(0, &readfds, NULL, NULL, NULL);

        if( activity == SOCKET_ERROR )
            WsaThrowErrorWithCleaningSockets("Select()", client_socket, master);
        
        // If master has an activity
        // It means there is an incoming connection request
        if(FD_ISSET(master, &readfds))
            HandleServerMaster(master, address, msg);
        // Otherwise the ther exists some IO operation on one of the client sockets
        // which means one of the clients has sent a request
        else
            HandleServerClient(client_socket, address, buffer); 
    }
   
    ///////////////////////////////////////////
    // Cleanup the resources and exit 
    ///////////////////////////////////////////
    
    CleanResources(master, client_socket);

    return 0;
}
