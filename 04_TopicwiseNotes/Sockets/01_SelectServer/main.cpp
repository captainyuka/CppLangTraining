#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT "32000" // Port we listen
#define BACKLOG 10   // Param to listen,how many incoming connections can queue up

#pragma comment(lib, "Ws2_32.lib")

void handle(SOCKET newsock, fd_set* set){
	// send, recv , closesocket
	// Call FD_CLR(newsock, set) on disconnection
}

void throw_error(const char* err_msg){
	fprintf(stderr, err_msg);
	printf("\tWSA Error Code %d", WSAGetLastError());
	WSACleanup();
	exit(1);
}


int main(){
	WORD wVersion = MAKEWORD(2, 2); 		// Store WSA Version
	WSADATA wsaData;				// WSA: Windows Socket Address (probably :) )
	int iResult;					// Store the init result of WSA	
	SOCKET sock;					// Server socket
	// file descriptor sets are used with select()
	// selects listens this socket set
	// and returns any socket that has notification or any change
	fd_set socks;					 
	fd_set readsocks;
	SOCKET maxsock;					// Maximum socket number found in the socket set
	int reuseaddr = 1;  				// True, let the same address be used by others
	struct addrinfo hints, *res;			// Store address info

	// We always start with initializing the Winsock	
	// Initialize Winsock
	if( iResult = WSAStartup(wVersion, &wsaData) != 0 ){
	    printf("WSAStartup failed: %d\n", wsaData);
	    return 1;
	}

	// Get the address info
	ZeroMemory(&hints, sizeof(hints));		// init hints as zero value
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if(getaddrinfo(NULL, PORT, &hints, &res) != 0)
	    throw_error("getaddrinfo");

	// Create the socket
	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if(sock == -1)
	    throw_error("socket");
	
	// Enable the socket to reuse the address
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, 
				(const char*)&reuseaddr, 
				sizeof(int)) == SOCKET_ERROR)
	    throw_error("setsockopt");

	// Bind to the address
	if(bind(sock, res->ai_addr, res->ai_addrlen) == SOCKET_ERROR)
	    throw_error("bind");
	
	// Listen
	if(listen(sock, BACKLOG) == SOCKET_ERROR)
	    throw_error("listen");

	// Set up the fd_set
	FD_ZERO(&socks);
	FD_SET(sock, &socks);
	maxsock = sock;

	while(1){
	    SOCKET s;
	    readsocks = socks;
	    if(select(maxsock+1, &readsocks, NULL, NULL, NULL) == SOCKET_ERROR)
	        throw_error("select");

	    for(s=0; s <= maxsock; s++)
		if(FD_ISSET(s, &readsocks)){
		    printf("Socket %d was ready\n", s);
		    if(s == sock){
		        // if the selected socket is the server socket
			// this means there exists a NEW CONNECTION request
			SOCKET newsock;
			struct sockaddr_in their_addr;
			int size = sizeof(struct sockaddr_in);
			
			newsock = accept(sock, (struct sockaddr*)&their_addr, &size);
			if( newsock != INVALID_SOCKET ){
			    printf("Got a connection from %s on port %d\n",
					    inet_ntoa(their_addr.sin_addr),
					    htons(their_addr.sin_port));
			    // Add the new socket to the socket list of the select
			    FD_SET(newsock, &socks);
			    if(newsock > maxsock)
			        maxsock = newsock;
			}
			else
			    perror("accept");
		    
		    }
		}
	    	else
		    handle(s, &socks);

	}

	closesocket(sock);
	WSACleanup();

}

