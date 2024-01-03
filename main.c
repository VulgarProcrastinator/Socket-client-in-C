
#include "lib/socketutil.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int createTCPIpv4Socket(){return socket(AF_INET, SOCK_STREAM, 0);};
    // AF_INET - address family INET A.K.A. IPv4
    // SOCK_STREAM - TCP socket would assume Datagram sockets are for UDP
    // 0 - is for "saying we want an IP layer to be used after our Transport layer"

struct sockaddr_in* createIpv4Address(char *ip, int port){

    //ip ="142.250.188.46";
    
    struct sockaddr_in* address = malloc(sizeof( struct sockaddr_in));
    // struct sockaddr_in {
    //     short int sin_family; // Address family
    //     unsigned short int sin_port; // Port number
    //     struct in_addr sin_addr; // Internet address that is 32-bits, or 4 bytes
    //     unsigned char sin_zero[8]; // Set to zero
    // };
    address->sin_family = AF_INET;
    address->sin_port = htons(port); // will flip the bites to convert in to Network Byte Order
    inet_pton(AF_INET, ip, &address->sin_addr.s_addr); // the last part is where it will return the value
    // after spesifying presentation form(version of IP) it will convert a string into an int

    return address;
}

int main(){

    int socketFD = createTCPIpv4Socket(); 
    // socketFD is to get a `file descriptor`

    struct sockaddr_in* address = createIpv4Address("142.250.188.46", 80);

    int result = connect(socketFD, address, sizeof(*address));
    // connect A.K.A. fansy write()

    if (result == 0){
        printf("Connected successfully \n");
    }else {
        fprintf(stderr, "Failed to connect \n");
    }

    char* message;

    message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";

    send(socketFD, message, strlen(message), 0);

    char buffer[1024];
    recv(socketFD, buffer, 1024, 0);

    printf("Responce: %s \n", buffer);

    return 0;
}
