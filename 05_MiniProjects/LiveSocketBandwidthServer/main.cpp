#include <stdio.h>   
#include <string.h>
#include <stdlib.h>
#include <regex>
#include <sstream>
#include <string>
#include <winsock2.h>
#include "PcapLiveDeviceList.h"

// add -l"ws2_32" arg to g++ or uncomment the following line
//#pragma comment(lib, "ws2_32.lib")              // Required for windows socket 2 usage(win32 sockets)

#define TRUE 1
#define FALSE 0

// The following macros planned to be taken as argument to the main
// That is why we allocate the resources dynamically rather than staticly
// These are only used in main when we declare variables, just replace macro with arg
#define MAX_NUMBER_OF_CLIENTS 30
#define MAX_RECV_BUFFER_SIZE 1024
#define MAX_SOCKET_TO_TRACK_PER_CLIENT 20
#define MAX_LIVE_DEVICES 50


/**
 * A struct for collecting packet statistics on an IP:PORT
 */
struct PacketStats
{
    // IP:PORT is the socket we are trying to listen
    std::string ip;                 
    int port;                     
    int ms;                     // Listener inform period
    long int last_millisecond = -1;
    long int packet_count = 0;
    long int packets_per_millisecond = 0;

	void Clear() { 
        last_millisecond = -1; 
        packet_count = 0;
        packets_per_millisecond = 0; 
    }

	/**
	 * a PacketStats object is identified by its IP:PORT
	 */
	PacketStats(std::string ip, int port, int ms) { 
        this->ip = ip;
        this->port = port;
        this->ms = ms;
        Clear(); 
    }

	/**
	 * Count number of packets and also calculate bandwidth at every 100millisecond.
     * This function is called whenever a packet received.
     *
     * @param raw_packet unprocessed packets with timestamp 
     * @returns the timestamp of the last packet in milliseconds
	 */
    long int CountPackets(pcpp::RawPacket* raw_packet){
        // Raw packet contains timestamp of the packet
        long int packet_timestamp_second = raw_packet->getPacketTimeStamp().tv_sec;
        long int packet_timestamp_nsecond = raw_packet->getPacketTimeStamp().tv_nsec; 
        
        // Work on millisecond units rather than second or nanosecond.
        long int packet_millisecond = packet_timestamp_second * 1000 + packet_timestamp_nsecond  / 1000000;
        int diff_ms;

        // According to accumulated packets, compute the speed of the socket
        // When the last_second about to change, update the bandwidth of the socket
        
        if(last_millisecond != -1){
            diff_ms = packet_millisecond - this->last_millisecond;
            if(diff_ms > 100){
                this->last_millisecond = packet_millisecond;
                printf("DEBUG:::Bandwidth: %ld Kbps\n", packet_count);
                this->packets_per_millisecond = packet_count;
                this->packet_count = 0;
            }
        }else{
             this->last_millisecond = packet_millisecond;
             this->packet_count = 0;  
        } 

        ++(this->packet_count);
        return packet_millisecond;
	}
};

struct PacketExtras{
    PacketStats*** client_stats;
    SOCKET* client_sockets;
    int max_number_of_clients;
    int max_socket_to_track_per_client;
    int curr_client_index;
    int curr_socket_index;
};

//TODO: Integrate into other places where we use ip:port:ms
struct SocketData{
    std::string ip;
    int port;
    int ms;
};

SOCKET SetupTheServer(int port, struct sockaddr_in* server, SOCKET* client_socket);
void StartTheServer(SOCKET master, int max_wait_queue_size, struct sockaddr_in server, SOCKET* client_socket);
void SetupTheFdSet(SOCKET master, fd_set* readfds_ptr, SOCKET* client_socket);
void HandleServerMaster(SOCKET master, SOCKET* client_socket, const char* msg, int max_number_of_clients);
void HandleServerClient(fd_set* readfds_ptr, SOCKET* client_sockets, 
                        char* buffer, int max_number_of_clients, int max_recv_buffer_size,
                        PacketStats*** packet_stats,int max_socket_count_per_client,
                        pcpp::PcapLiveDevice** devices);
 
void CleanResources(SOCKET master, SOCKET* client_socket);
void WsaThrowError(const char* msg);
void WsaThrowErrorWithCleaningSockets(const char* msg, SOCKET* client_sockets, SOCKET server);

void StopLiveCapture(pcpp::PcapLiveDevice* dev, PacketStats& stats);
pcpp::PcapLiveDevice* SetupAndStartLiveCapture(PacketStats*** packet_stats, int client_index, 
                                               int socket_index, SOCKET* client_sockets, 
                                               int max_number_of_clients,
                                               int max_socket_to_track_per_client);
void PrintDeviceInfo(pcpp::PcapLiveDevice* dev);
static void OnPacketArrives(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);

int main(int argc, char* argv[])
{
    WSADATA wsa;                                // Windows Socket A. Data, Required to be initialized to use Windows Sockets
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
    int max_socket_count_per_client = MAX_SOCKET_TO_TRACK_PER_CLIENT; 
    int max_live_devices = MAX_LIVE_DEVICES;

    // Allocate PacketStats for each client
    PacketStats*** stats = (PacketStats***)malloc(sizeof(PacketStats**) * max_number_of_clients);
    for(i = 0; i < max_number_of_clients; ++i)
        stats[i] = NULL; 

    ///////////////////////////////////////////
    // Init variables and Setup the Server
    ///////////////////////////////////////////
    
    // Initialize server basics, prepares for setup
    client_socket = (SOCKET*)malloc(sizeof(SOCKET) * max_number_of_clients);
    buffer = (char*)malloc((max_recv_buffer_size+1) * sizeof(char));      // Extra +1 for null termination
     
    // init all sockets as invalid, later we will put valid ones
    for(i = 0; i < max_number_of_clients; ++i)
        client_socket[i] = 0;
     
    // Allocate an array for live devices that we will later listen
    pcpp::PcapLiveDevice** devices = new pcpp::PcapLiveDevice*[max_live_devices];
    for(i=0; i < max_live_devices; ++i)
        devices[i] = NULL;

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
            // Otherwise the there exists some IO operation on one of the client sockets
            // which means one of the clients has sent a request
            HandleServerClient(&readfds, client_socket, buffer, MAX_NUMBER_OF_CLIENTS, MAX_RECV_BUFFER_SIZE, 
                               stats, max_socket_count_per_client, devices ); 
    }

    CleanResources(master, client_socket);                  // Clean up the resources before quiting 

    return 0;
}



void InformTheClient(SOCKET client_socket, long int bandwidth, long int timestamp_in_ms){
    // SOCKET, char*, int  
    //send(client_socket, buffer, buffer_str_len, 0); 
    
    std::ostringstream out;
    out << "BANDWIDTH=" << bandwidth << ", TIMESTAMP=" << timestamp_in_ms << '\0';
    std::string tmp = out.str();
    const char* buffer =  tmp.c_str();
    int buffer_len = strlen(buffer);
    send(client_socket, buffer, buffer_len, 0);
}

/**
 * Control whether we need to send bandwidth data to any of the clients
 * and also count the number of packets received.
 *
 * Callback function for the async capture which is called each time a packet is captured.
 *
 * @param packet is the packet that just arrived.
 * @param dev is the device that we listen to.
 * @param cookie is a way to pass special parameters to OnPacketArrives function.
 */
static void OnPacketArrives(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie){
    void InformTheClient(SOCKET client_socket, long int bandwidth, long int timestamp_in_ms);
    long int timestamp;                                 // Packet timestamp in milliseconds
    int client, socket;
    int max_n_clients;
    int max_n_sockets_per_client;

    SOCKET* client_sockets;
    PacketExtras* extras = (PacketExtras*)cookie;
    int client_index = extras->curr_client_index;
    int socket_index = extras->curr_socket_index;
    max_n_clients = extras->max_number_of_clients;
    max_n_sockets_per_client = extras->max_socket_to_track_per_client;
    client_sockets = extras->client_sockets;

    PacketStats*** client_stats = extras->client_stats; // Array of client tract arrs
    PacketStats** client_track_arr;                     // Array of PacketStats* for a client
    PacketStats* socket_stats;                          // A socket of the current client
	timestamp = client_stats[client_index][socket_index]->CountPackets(packet);
    

    for(client = 0; client < max_n_clients; ++client){
        client_track_arr = client_stats[client];        // Take the next client

        for(socket = 0; 
            socket < max_n_sockets_per_client && client_track_arr[socket] != NULL; 
            ++socket){
            socket_stats = client_track_arr[socket];
            if(socket_stats->last_millisecond != -1)
                if(  (timestamp - socket_stats->last_millisecond)  >= socket_stats->ms )
                    InformTheClient(client_sockets[client], socket_stats->packets_per_millisecond, timestamp);    
        }
    }

}

/**
 * Prints the device details to the console.
 *
 * @param dev is the device to print its details.
 */
void PrintDeviceInfo(pcpp::PcapLiveDevice* dev){
	printf("Interface info:\n");
	printf("   Interface name:        %s\n", dev->getName());
	printf("   Interface description: %s\n", dev->getDesc());
	printf("   MAC address:           %s\n", dev->getMacAddress().toString().c_str());
	printf("   Default gateway:       %s\n", dev->getDefaultGateway().toString().c_str());
	printf("   Interface MTU:         %d\n", dev->getMtu());
	if (dev->getDnsServers().size() > 0)
		printf("   DNS server:            %s\n", dev->getDnsServers().at(0).toString().c_str());
}

/**
 * Sets up a live capture and start capturing.
 *
 * @param stats is the stats of the current device
 * @param interfaceIPAddr is the IP we are trying to listen
 * @returns a pointer to the device we are listening.
 */
pcpp::PcapLiveDevice* SetupAndStartLiveCapture(PacketStats*** packet_stats, int client_index, 
                                               int socket_index, SOCKET* client_sockets, 
                                               int max_number_of_clients,
                                               int max_socket_to_track_per_client){
    std::string interfaceIPAddr = packet_stats[client_index][socket_index]->ip;
    int port = packet_stats[client_index][socket_index]->port;
    
    PacketExtras* extras = new PacketExtras;
    extras->client_stats = packet_stats;
    extras->client_sockets = client_sockets;
    extras->curr_client_index = client_index;
    extras->curr_socket_index = socket_index;
    extras->max_number_of_clients = max_number_of_clients;
    extras->max_socket_to_track_per_client = max_socket_to_track_per_client;

	// find the interface by IP address
	pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(interfaceIPAddr.c_str());
	if (dev == NULL){
		printf("Cannot find interface with IPv4 address of '%s'\n", interfaceIPAddr.c_str());
		exit(1);
	}

	// Get device info
	// ~~~~~~~~~~~~~~~
    PrintDeviceInfo(dev);

    // open the device before start capturing/sending packets
	if (!dev->open()){
		printf("Cannot open device\n");
		exit(1);
	}

	// Async packet capture with a callback function
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	printf("\nStarting async capture using filters...\n");

    // create a filter instance to capture only traffic on the specified port
	pcpp::PortFilter portFilter(port, pcpp::SRC_OR_DST);

    // create an AND filter to combine multiple filters - capture only traffic on  the specified port
	pcpp::AndFilter andFilter;
	andFilter.addFilter(&portFilter);

	// set the filter on the device
	dev->setFilter(andFilter);

	printf("\nStarting async packet capture with a filter in place...\n");

    // start capture in async mode. 
    // Give a callback function to call to 
    // whenever a packet is captured and the stats object as the cookie
	dev->startCapture(OnPacketArrives, (void*)extras);

    return dev;
}

/**
 * Sets up the server and returns the socket.
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
 * Deallocates a client's stats.
 *
 * @param packet_stats is an array of PacketStats**.
 *        Each client has PacketStats* array.
 *        We keep track of each stat a client wants as PacketStats*
 *        because of the performance issues. We only move pointers.
 *        Remember PacketStats object for each client is updated millions of times per second.
 * @param client_index is the index of the client inside of the packet_stats or client_socket array
 */
void DeallocateClientStats(PacketStats*** packet_stats, int client_index){
    PacketStats** selected_client_data = packet_stats[client_index];
    packet_stats[client_index] = NULL;
    int i;

    for(i = 0; selected_client_data[i] != NULL; ++i)
        free(selected_client_data[i]);
    free(selected_client_data);
}

/**
 * Handles proper or unexpected disconnection requests.
 *
 * @param address is the client address data.
 * @param s is the socket of the client
 * @param client_socket is the list of client sockets of the server
 * @param i is the index of the current client in the client_socket array
 */
void DisconnectTheClient(struct sockaddr_in address, SOCKET s, SOCKET* client_socket, 
                         PacketStats*** packet_stats, int client_index){
    void DeallocateClientStats(PacketStats*** packet_stats, int client_index);

    // Check if somebody disconnected unexpectedly
    int error_code = WSAGetLastError();

    if(error_code == WSAECONNRESET){
        fprintf(stderr, "Host disconnected unexpectedly:::IP = %s:::PORT = %d\n",
                inet_ntoa(address.sin_addr),
                ntohs(address.sin_port)); 
        closesocket(s);
        DeallocateClientStats(packet_stats, client_index);
    }else
       fprintf(stderr, "recv failed with error code: %d", error_code);
}


/**
 * Cleans the trailing \r\n in windows, \n in unix based systems.
 */
char* CleanMsg(char* msg, int len){

    while(msg[len-1]=='\r' || msg[len-1]=='\n')
        --len;
    
    msg[len] = '\0';
    return msg;
}

/**
 * Searches whether the current client already listens to the given IP:PORT
 *
 * @param ip is the IP of the socket 
 * @param port is the port of the socket
 * @param packet_stats is an array of client of interest's track lists
 * @param client_index is the index of the current client inside paket_stats
 * @param max_socket_count max number of sockets each client could have in his track list.
  @return i index of the socket inside of the client socket track list.
 *         -1 if not found.
 */
int SearchIfSocketAlreadyExists(std::string ip, int port,
                                PacketStats*** packet_stats, int client_index,
                                int max_socket_count){

    PacketStats** client_stats = packet_stats[client_index];
    int found = FALSE;
    int i = 0;
    
    // Search if the current socket is already found on the client's list
    while(client_stats[i] != NULL && found == FALSE && i < max_socket_count){
        if(client_stats[i]->port == port && ip.compare(client_stats[i]->ip) == 0)
            found = TRUE;
        ++i;
    }

    if(found == FALSE)
        return -1;                  // Not Found
    
   // While loop increments one additional in the last loop
   return --i;
}

int AddSocket(std::string ip, int port, int ms, 
              PacketStats*** packet_stats, int client_index, int max_socket_count,
              pcpp::PcapLiveDevice** devices,
              SOCKET* client_sockets, int max_number_of_clients){

    int socket_index = 0;
    int i = SearchIfSocketAlreadyExists(ip, port, packet_stats, client_index, max_socket_count); 
    if(i > 0){
        fprintf(stderr, "This socket is already in trace list of some other client.\n");
        return -1;          // The Client already listens this socket, discard the request
    }
    while(socket_index < max_socket_count && packet_stats[client_index][socket_index] != NULL)
        ++socket_index;
    
    if(socket_index >= max_socket_count){
        fprintf(stderr, "The Client cannot register any more sockets, max_socket_count has been already reached.\n");
        return -1;
    }

    PacketStats* stats = new PacketStats(ip, port, ms);  
    packet_stats[client_index][i] = stats; 
    devices[client_index] = SetupAndStartLiveCapture(packet_stats, client_index, 
                                                     socket_index, client_sockets,
                                                     max_number_of_clients,
                                                     max_socket_count);
    return 0;
}

/**
 * Deletes a socket from given client's track list.
 * We no longer listen that port from now on.
 *
 * @param ip is the IP of the socket 
 * @param port is the port of the socket
 * @param packet_stats is an array of client track lists
 * @param client_index is the index of the current client inside paket_stats
 * @param max_socket_count max number of sockets each client could have its track list.
 * @returns -1 in case of error, >= 0 when there exists no error
 */
int DelSocket(std::string ip, int port,
              PacketStats*** packet_stats, int client_index, int max_socket_count,
              pcpp::PcapLiveDevice** devices){
    PacketStats** client_stats = packet_stats[client_index];
    int i;

    if( (i = SearchIfSocketAlreadyExists(ip, port, packet_stats, client_index, max_socket_count)) == -1)
        return -1;                              // Socket is not found
   
    delete client_stats[i];
    client_stats[i] = NULL;
    devices[i]->stopCapture();       // Stop the device
    devices[i] = NULL;
    return 0;
}

SocketData ClientCmdToData(std::string cmd){
    size_t pos = 0;
    int i = 0;
    std::string delimiter = ":";
    std::string token, ip_str, port_str, ms_str;
    SocketData data;

    while((pos = cmd.find(delimiter)) != std::string::npos){
        token = cmd.substr(0, pos);
        if( i == 1 )
            ip_str = token;
        else if( i == 2 )
            port_str = token;
        cmd.erase(0, pos + delimiter.length());
    }
    ms_str = cmd;

    data.ip = ip_str;
    data.port = std::stoi( port_str );
    data.ms = std::stoi( ms_str );

    return data;
}

/**
 * Callback function for client interactiopn with server.
 * Provides dynamic command based communication line.
 *
 * Supported Commands:
 *    ADD:IP:PORT:MS      ex/ ADD:185.85.188.58:500
 *    DEL:IP:PORT:MS      ex/ DEL:185.85.188.58:500
 *
 * @param client_socket is the socket of the client to be handled.
 * @param address is the details of the client socket.
 * @param buffer is the receive buffer of the server.
 * @param buffer_str_len is the capacty of the server buffer.
 * @param packet_stats is an array of PacketStats** array.
 *        It is used to keep track of client target socket speeds.
 *        Each client has an array of PacketStats* which is PacketStats**
 *        and all clients data inside PacketStats***.
 *        We keep tract of PacketStats as pointer because of performance issues since we
 *        move these PacketStats every time a packet comes, the performance is critical.
 *        The performance is critical since we get 100s of Millions packet per second.
 * @param client_index is the index of the client inside packet_stats array
 * @param max_socket_count_per_client is the max number of socket a client could listen.
 */
void HandleClientRequest(SOCKET client_socket, struct sockaddr_in address, 
                         char* buffer, int buffer_str_len,
                         PacketStats*** packet_stats, int client_index, int max_socket_count_per_client,
                         pcpp::PcapLiveDevice** devices,
                         SOCKET* client_sockets, int max_number_of_clients
                         ){
    char* CleanMsg(char* msg, int len);
    SocketData ClientCmdToData(std::string cmd);
    SocketData data;
    buffer[buffer_str_len] = '\0';
    printf("%s:%d - %s\n", inet_ntoa(address.sin_addr),
                           ntohs(address.sin_port),
                           buffer);
    buffer = CleanMsg(buffer, buffer_str_len);
    buffer_str_len = strlen(buffer); 
    std::string str;
    str += buffer;

    std::regex add_cmd_pattern("(ADD:)(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(:[0-9]*)");
    std::regex del_cmd_pattern("(DEL:)(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(:[0-9]*)");

    if( regex_match(str.begin(), str.end(), add_cmd_pattern) ){
        data = ClientCmdToData(str);
        AddSocket(data.ip, data.port, data.ms, packet_stats, client_index, max_socket_count_per_client, devices,
                  client_sockets, max_number_of_clients);
    }
    else if( regex_match(str.begin(), str.end(), del_cmd_pattern) ){
        data = ClientCmdToData(str);
        DelSocket(data.ip, data.port, packet_stats, client_index, max_socket_count_per_client, devices);
    }
    else
        printf("No Match\n");
    
    // SOCKET, char*, int  
    //send(client_socket, buffer, buffer_str_len, 0); 
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
 * @param packet_stats is an array of PacketStats** array.
 *        It is used to keep track of client target socket speeds.
 *        Each client has an array of PacketStats**, all clients data inside PacketStats***.
 *        Each client array contains an array of PacketStats*. 
 *        We keep tract of PacketStats as pointer because of performance issues since we
 *        move these PacketStats every time a packet comes, the performance is critical.
 *
 * */
void HandleServerClient(fd_set* readfds_ptr, SOCKET* client_sockets, 
                        char* buffer, int max_number_of_clients, int max_recv_buffer_size,
                        PacketStats*** packet_stats,int max_socket_count_per_client,
                        pcpp::PcapLiveDevice** devices){
     
    void DisconnectTheClient(struct sockaddr_in address, SOCKET s, SOCKET* client_socket, 
                             PacketStats*** packet_stats, int client_index);
    void HandleClientRequest(SOCKET client_socket, struct sockaddr_in address, 
                             char* buffer, int buffer_str_len,
                             PacketStats*** packet_stats, int client_index, int max_socket_count_per_client, 
                             pcpp::PcapLiveDevice** devices, SOCKET* client_sockets, int max_number_of_clients
                             ); 
    SOCKET curr_client_socket;
    int valread;
    struct sockaddr_in address;
    int addrlen = sizeof(struct sockaddr_in);
    int i;

    for(i = 0; i < max_number_of_clients; ++i)
        if(FD_ISSET((curr_client_socket=client_sockets[i]), readfds_ptr)){
            // Get details of the client
            getpeername(curr_client_socket, (struct sockaddr*)&address, &addrlen);

            // Check if it was for closing
            // and also read the incoming msg
            // do not forget, recv doeos not place a null at the end of str
            valread = recv(curr_client_socket, buffer, max_recv_buffer_size, 0);

            if(valread == SOCKET_ERROR)
                DisconnectTheClient(address, curr_client_socket, client_sockets, packet_stats, i);
            else if(valread == 0){
                // Somebody disconnected, print the client's details
                printf("Host disconnected:::IP = %s, PORT = %d\n", 
                        inet_ntoa(address.sin_addr), 
                        ntohs(address.sin_port) );
                // Close the socket and mark as 0 in the client list for reuse
                closesocket(curr_client_socket);
                client_sockets[i] = 0;
            }else       
                // client has sent a msg which is now in buffer with length of valread
                HandleClientRequest(curr_client_socket, address, buffer, valread, 
                                    packet_stats, i, max_socket_count_per_client,
                                    devices, client_sockets, max_number_of_clients); 
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




