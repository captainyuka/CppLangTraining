#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(void){
    WSADATA wsa;
    const char* hostname = "www.google.com";
    char ip[100];
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    printf("Initializing Winsock");

    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0){
        printf("Failed\n");
        return 1;
    }

    printf("Initialised\n");
    
    if( (he = gethostbyname(hostname)) == NULL){
        printf("gethostbyname failed\n");
        return 1;
    }
    
    addr_list = (struct in_addr**)he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; ++i)
        strcpy(ip, inet_ntoa(*addr_list[i]));       // Cast the 

    printf("%s resolved to:%s\n", hostname, ip);

return 0;

}
