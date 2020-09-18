#include <stdio.h>   
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include "PcapLiveDeviceList.h"
#include "PlatformSpecificUtils.h"       // Use cross platform sleep method


#pragma comment(lib, "ws2_32.lib")              // Required for windows socket 2 usage(win32 sockets)

#define TRUE 1
#define FALSE 0

// The following macros planned to be taken as param to main
// That is why we allocate the resources dynamically rather than staticly
#define MAX_NUMBER_OF_CLIENTS 30
#define MAX_RECV_BUFFER_SIZE 1024

// Functions related to the Server
SOCKET SetupTheServer(int port, struct sockaddr_in* server, SOCKET* client_socket);
void StartTheServer(SOCKET master, int max_wait_queue_size, struct sockaddr_in server, SOCKET* client_socket);
void SetupTheFdSet(SOCKET master, fd_set* readfds_ptr, SOCKET* client_socket);
void HandleServerMaster(SOCKET master, SOCKET* client_socket, const char* msg, int max_number_of_clients);
void HandleServerClient(fd_set* readfds_ptr, SOCKET* client_socket, char* buffer, int max_number_of_clients, int max_recv_buffer_size);

// Helper functions for the server
void CleanResources(SOCKET master, SOCKET* client_socket);
void WsaThrowError(const char* msg);
void WsaThrowErrorWithCleaningSockets(const char* msg, SOCKET* client_sockets, SOCKET server);

/**
 * A struct for collecting packet statistics
 */
struct PacketStats
{
	int ipv4PacketCount;
	int tcpPacketCount;
	int udpPacketCount;
    
    long int last_second = -1;
    long int packet_count = 0; 
	
    /**
	 * Clear all stats
	 */
	void clear() { ipv4PacketCount = 0; tcpPacketCount = 0; udpPacketCount = 0; last_second = -1; packet_count = 0;}

	/**
	 * Constructor
	 */
	PacketStats() { clear(); }

	/**
	 * Collect stats from a packet
	 */
	void consumePacket(pcpp::Packet& packet)
	{
		if (packet.isPacketOfType(pcpp::IPv4))
			ipv4PacketCount++;
		if (packet.isPacketOfType(pcpp::TCP))
			tcpPacketCount++;
		if (packet.isPacketOfType(pcpp::UDP))
			udpPacketCount++;
	   
        pcpp::RawPacket* raw_packet = packet.getRawPacket();
        long int packet_timestamp_second = raw_packet->getPacketTimeStamp().tv_sec;
        long int packet_timestamp_nsecond = raw_packet->getPacketTimeStamp().tv_nsec; 
        //printf("Packet Timestamp-> sec=%ld - nsec=%ld\n", packet_timestamp_second, packet_timestamp_nsecond);
        
        if( packet_timestamp_second != last_second && last_second != -1){
           last_second = packet_timestamp_second;
           printf("Bandwidth: %ld pps\n", packet_count);
           packet_count = 0;
        }else if(last_second == -1){
            last_second = packet_timestamp_second;
            packet_count = 0;
        }

        ++packet_count;
	}

	/**
	 * Print stats to console
	 */
	void printToConsole()
	{
		printf("IPv4 packet count:     %d\n", ipv4PacketCount);
		printf("TCP packet count:      %d\n", tcpPacketCount);
		printf("UDP packet count:      %d\n", udpPacketCount);
	}
};


/**
 * A callback function for the async capture which is called each time a packet is captured
 */
static void onPacketArrives(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie)
{
	// extract the stats object form the cookie
	PacketStats* stats = (PacketStats*)cookie;

	// parsed the raw packet
	pcpp::Packet parsedPacket(packet);

	// collect stats from packet
	stats->consumePacket(parsedPacket);
}

void PrintDeviceInfo(pcpp::PcapLiveDevice* dev){

	// before capturing packets let's print some info about this interface
	printf("Interface info:\n");
	// get interface name
	printf("   Interface name:        %s\n", dev->getName());
	// get interface description
	printf("   Interface description: %s\n", dev->getDesc());
	// get interface MAC address
	printf("   MAC address:           %s\n", dev->getMacAddress().toString().c_str());
	// get default gateway for interface
	printf("   Default gateway:       %s\n", dev->getDefaultGateway().toString().c_str());
	// get interface MTU
	printf("   Interface MTU:         %d\n", dev->getMtu());
	// get DNS server if defined for this interface
	if (dev->getDnsServers().size() > 0)
		printf("   DNS server:            %s\n", dev->getDnsServers().at(0).toString().c_str());
}

pcpp::PcapLiveDevice* SetupAndStartLiveCapture(PacketStats& stats, std::string interfaceIPAddr){
    // IPv4 address of the interface we want to sniff
//	std::string interfaceIPAddr = "185.85.188.58";

	// find the interface by IP address
	pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(interfaceIPAddr.c_str());
	if (dev == NULL)
	{
		printf("Cannot find interface with IPv4 address of '%s'\n", interfaceIPAddr.c_str());
		exit(1);
	}

	// Get device info
	// ~~~~~~~~~~~~~~~
    PrintDeviceInfo(dev);

    // open the device before start capturing/sending packets
	if (!dev->open())
	{
		printf("Cannot open device\n");
		exit(1);
	}

	// Async packet capture with a callback function
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	printf("\nStarting async capture...\n");

	// start capture in async mode. Give a callback function to call to whenever a packet is captured and the stats object as the cookie
	dev->startCapture(onPacketArrives, &stats);

    return dev;
}

void StopLiveCapture(pcpp::PcapLiveDevice* dev, PacketStats& stats){
    // stop capturing packets
	dev->stopCapture();

	// print results
	printf("Results:\n");
	stats.printToConsole();

	// clear stats
	stats.clear();
}
/*
void FilterCapture(pcpp::PcapLiveDevice* dev, PacketStats& stats){
	// Using filters
	// ~~~~~~~~~~~~~

	// create a filter instance to capture only traffic on port 80
	pcpp::PortFilter portFilter(80, pcpp::SRC_OR_DST);

	// create a filter instance to capture only TCP traffic
	pcpp::ProtoFilter protocolFilter(pcpp::TCP);

	// create an AND filter to combine both filters - capture only TCP traffic on port 80
	pcpp::AndFilter andFilter;
	andFilter.addFilter(&portFilter);
	andFilter.addFilter(&protocolFilter);

	// set the filter on the device
	dev->setFilter(andFilter);

	printf("\nStarting packet capture with a filter in place...\n");

	// start capture in async mode. Give a callback function to call to whenever a packet is captured and the stats object as the cookie
	dev->startCapture(onPacketArrives, &stats);

	// sleep for 10 seconds in main thread, in the meantime packets are captured in the async thread
	PCAP_SLEEP(10);

	// stop capturing packets
	dev->stopCapture();

	// print results - should capture only packets which match the filter (which is TCP port 80)
	printf("Results:\n");
	stats.printToConsole();


	// close the device before application ends
	dev->close();
}
*/
/**
 * main method of the application
 */
int main(int argc, char* argv[])
{
    PacketStats stats;
    /*pcpp::PcapLiveDevice* dev =*/// SetupAndStartLiveCapture(stats);
     
    ///////////////////////////////////////////
    // Declarations
    ///////////////////////////////////////////

    WSADATA wsa;                               // Windows Socket A. Data, Required to be initialized to use Windows Sockets
    SOCKET master;                              // Server master's SOCKET
    SOCKET* client_socket;                      // List of client SOCKETs that has connected to the server master
    struct sockaddr_in server;                  // Contains details of the server socket, like IPV4, its port etc.
    int activity;                               // Acitivity notification from select()[either new connection or client request]
    char* msg = "EACHO Daemon v1.0 \r\n";       // First msg to send to the client when it first get connected to the master
    char* buffer;                               // Server receive buffer, has a max length that has been taken as parameter from cmd
    fd_set readfds;                             // Set of file descriptors
    int i;

    // TODO: Take the following variables as argument to main
    int max_number_of_clients = MAX_NUMBER_OF_CLIENTS;
    int max_recv_buffer_size = MAX_RECV_BUFFER_SIZE;
     
    ///////////////////////////////////////////
    // Init variables and Setup the Server
    ///////////////////////////////////////////
    
    // Initialize server basics, prepares for setup
    client_socket = (SOCKET*)malloc(sizeof(SOCKET) * max_number_of_clients);
    buffer = (char*)malloc((max_recv_buffer_size+1) * sizeof(char));      // Extra +1 for null termination
     
    // init all sockets as invalid, later we will put valid ones
    for(i = 0; i < max_number_of_clients; ++i)
        client_socket[i] = 0;
    
    // Init the WSA
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        fprintf(stderr, "Failed to startup the WSA:: WSA Error %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
  

    // Sets up the server and returns the server master
    master = SetupTheServer(8888, &server, client_socket);  

    // Start the server with a wait queue size of 10 
    StartTheServer(master, 10, server, client_socket);
  
    ///////////////////////////////////////////
    // Accept the client requests and 
    // handle them asynchronously using polling
    // with the help of select()
    ///////////////////////////////////////////
    
    fprintf(stderr, "DEBUG:::::Waiting for incoming connections");

    // The following while loop first lets the select() function trace all the sockets related to this server.
    // we run the select() with infinite waiting which means up until any notication being generated
    // by some socket, server process will be waiting, and when notification exists, cpu schedules this process
    // whenever the cpu is available. 
    // 
    // Then we check the notification, if the master has a notification,
    //      this means that there is a new connection request to the server, we handle it, 
    // if a client has a notification
    //      this means we have a reques from that client, server handles the request
    while(TRUE){                                                                // Server runs indefinitely
        // Get prepared for select() call
        // Make sure select() traces server master and its clients for any notification
        SetupTheFdSet(master, &readfds, client_socket);
        
        // Wait for an activity on any of the sockets
        activity = select(0, &readfds, NULL, NULL, NULL);                       // timeout is NULL, which means we wait indefinitely
        
        // Check what the activity is about
        if( activity == SOCKET_ERROR )
            WsaThrowErrorWithCleaningSockets("Select()", client_socket, master);
        
        if(FD_ISSET(master, &readfds))
            // If master has an activity
            // It means there is an incoming connection request
             HandleServerMaster(master, client_socket, msg, MAX_NUMBER_OF_CLIENTS);
        else
            // Otherwise the ther exists some IO operation on one of the client sockets
            // which means one of the clients has sent a request
            HandleServerClient(&readfds, client_socket, buffer, MAX_NUMBER_OF_CLIENTS, MAX_RECV_BUFFER_SIZE); 
    }
   
    CleanResources(master, client_socket);                  // Clean up the resources before quiting 

    return 0;
}


/**
 * Sets up the server socket return the socket.
 * 
 * @param port is the port of the server socket
 * @param server is the details of the server socket
 * @param client_socket is the list of client sockets
 *        client_socket var is only used to deallocate resources in case of error
 * @return return the server socket
 */
SOCKET SetupTheServer(int port, struct sockaddr_in* server, SOCKET* client_socket){  
    SOCKET master;

    // Create socket
    if( (master=socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
        WsaThrowErrorWithCleaningSockets("socket()", client_socket, -1);

    // Prepare the sockaddr_in structure
    server->sin_family = AF_INET;                // use IPv4
    server->sin_addr.s_addr = INADDR_ANY;        // Anyone can connect
    server->sin_port = htons( 8888 );            // Server will use 8888 port
    
    return master;
}

/**
 * Run the server on the specified master socket using given server details. 
 *
 * @param master is the server socket
 * @param max_wait_queue_size is the maximum number of clients that can wait 
 *        in the wait queue to be served by the server master when the master is busy.
 * @param client_socket is the list of client sockets
 *        client_socket var is only used to deallocate resources in case of error
 */
void StartTheServer(SOCKET master, int max_wait_queue_size, struct sockaddr_in server, SOCKET* client_socket){
    // Bind server to the specified port
    if( bind(master, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
        WsaThrowErrorWithCleaningSockets("bind()", client_socket, master);
    
    // Listen to incoming connections
    listen(master, max_wait_queue_size); 
}

/**
 * Prepares list of server socket file descriptors to be traced by the select().
 * Select function checks every one of the sockets inside of this list and returns
 * any change as notification to us. That is why here we include server master and
 * clients of the server to the list of file descriptors.
 *
 * @param master is the server socket
 * @param readfds_ptr is a pointer to the read file descriptor set
 *        readfds listens for any change to be read from the set of the sockets.
 * @param client_socket is the list of client sockets
 */
void SetupTheFdSet(SOCKET master, fd_set* readfds_ptr, SOCKET* client_socket){ 
    SOCKET s;
    int i;

    // Clear the socket fd set
    FD_ZERO(readfds_ptr);

    // Add the master socket to the fd set
    FD_SET(master, readfds_ptr);
    
    // Add child sockets to the fd set
    for(i=0; i < MAX_NUMBER_OF_CLIENTS; ++i)
        if((s=client_socket[i]) > 0)
            FD_SET(s, readfds_ptr);
} 


/**
 * Handles new connection requests to the server.
 *
 * @param master is the server socket
 * @param msg is the hello msg to be sent to the new connection.
 *
 */
void HandleServerMaster(SOCKET master, SOCKET* client_socket, const char* msg, int max_number_of_clients){
    SOCKET new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(struct sockaddr_in);
    int i;

    if((new_socket = accept(master, (struct sockaddr*)&address, (int*)&addrlen)) < 0)
        WsaThrowErrorWithCleaningSockets("Select()", client_socket, master);

    printf("New Sconnection:::Socket fd = %d:::IP = %s:::PORT = %d\n",
            new_socket,
            inet_ntoa(address.sin_addr),
            ntohs(address.sin_port));

    // Send new connection greeting message
    if(send(new_socket, msg, strlen(msg), 0) != (int)strlen(msg))
        fprintf(stderr, "Msg Sending Failed\n");
    else
        fprintf(stderr, "DEBUG::::: Msg Has been sent successfully\n");
    
    // Add the new socket to the array of sockets
    for(i = 0; i < max_number_of_clients; ++i)
        if(client_socket[i] == 0){
            client_socket[i] = new_socket;
            fprintf(stderr, "DEBUG:::::Adding socket to the list of sockets at index %d\n", i);
            break;
        } 
}

/**
 * Handles proper or unexpected disconnection requests.
 *
 * @param address is the client address data.
 * @param s is the socket of the client
 * @param client_socket is the list of client sockets of the server
 * @param i is the index of the current client in the client_socket array
 */
void DisconnectTheClient(struct sockaddr_in address, SOCKET s, SOCKET* client_socket, int i){
    // Check if somebody disconnected unexpectedly
    int error_code = WSAGetLastError();

    if(error_code == WSAECONNRESET){
       fprintf(stderr, "Host disconnected unexpectedly:::IP = %s:::PORT = %d\n",
               inet_ntoa(address.sin_addr),
               ntohs(address.sin_port)); 
       closesocket(s);
       client_socket[i] = 0;
    }else
       fprintf(stderr, "recv failed with error code: %d", error_code);
}

void HandleClientRequest(SOCKET s,struct sockaddr_in address, char* buffer, int buffer_str_len){
    // Echo back the msg that came in  
    buffer[buffer_str_len] = '\0';
    printf("%s:%d - %s\n", inet_ntoa(address.sin_addr),
                           ntohs(address.sin_port),
                           buffer);
    if( strstr(buffer,":") != NULL ){     
    	std::string interfaceIPAddr = "185.85.188.58";
        SetupAndStartLiveCapture(stats, interfaceIPAddr);
        
    }

    send(s, buffer, buffer_str_len, 0); 
}

/**
 * Works as part of the select(), serves the client who has sent request.
 * First checks all the sockets from the socket list
 * then if the socket has any notification checks it
 * the notification by reading from the socket
 * then handles all possiblilities: error, disconnection, incoming msg
 *
 * @param readfds_ptr pointer to the read file descriptor set of the select()
 * @param client_socket is the aray of sockets
 * @param buffer is the receive buffer of the server
 * @param max_number_of_clients is the client capacity of the server
 * @param max_rev_buffer_size is the capacty of the server buffer
 * */
void HandleServerClient(fd_set* readfds_ptr, SOCKET* client_socket, char* buffer, int max_number_of_clients, int max_recv_buffer_size){
     
    void DisconnectTheClient(struct sockaddr_in address, SOCKET s, SOCKET* client_socket, int i);
    SOCKET s;
    int valread;
    struct sockaddr_in address;
    int addrlen = sizeof(struct sockaddr_in);
    int i;

    for(i = 0; i < max_number_of_clients; ++i)
        if(FD_ISSET((s=client_socket[i]), readfds_ptr)){
            // Get details of the client
            getpeername(s, (struct sockaddr*)&address, &addrlen);

            // Check if it was for closing
            // and also read the incoming msg
            // do not forget, recv doeos not place a null at the end of str
            valread = recv(s, buffer, max_recv_buffer_size, 0);

            if(valread == SOCKET_ERROR)
                DisconnectTheClient(address, s, client_socket, i);
            else if(valread == 0){
                // Somebody disconnected, print the client's details
                printf("Host disconnected:::IP = %s, PORT = %d\n", 
                        inet_ntoa(address.sin_addr), 
                        ntohs(address.sin_port) );
                // Close the socket and mark as 0 in the client list for reuse
                closesocket(s);
                client_socket[i] = 0;
            }else       
                // client has sent a msg which is now in buffer with length of valread
                HandleClientRequest(s, address, buffer, valread); 
        }
}

/**
 * Cleans the resources related to sockets and WSA(Window Socket A.)
 *
 * @param master is the server socket
 * @param client_socket is an array of client sockets, may contain NULL spots at the end
 */
void CleanResources(SOCKET master, SOCKET* client_socket){ 
    // Make sure all client sockets has been deallocated
    while(client_socket != NULL)               // Traverse the array
        closesocket(*client_socket++);         // Close the current client socket

    // Deallocate the array itself
    free(client_socket);                      // Free the dynamically allocated client_sockets array 
    
    // Close the server master
    closesocket(master);

    // Deallocate Windows Socket related services
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
    
    if( server != (SOCKET)-1 )
        closesocket(server);                    // Close the ccurent server socket
    WSACleanup();                               // Clean the WSA resources
    exit(EXIT_FAILURE);                         // Exit the program with an error
}




