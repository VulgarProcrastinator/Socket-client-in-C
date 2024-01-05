
#include "lib/socketutil.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

int main(){

    int socketFD = createTCPIpv4Socket(); 
    // socketFD is to get a `file descriptor`

    struct sockaddr_in* address = createIpv4Address("127.0.0.1", 25000);

    int result = connect(socketFD, address, sizeof(*address));
    // run()
    // connect A.K.A. fansy write()

    if (result == 0){
        printf("Connected successfully \n");
    }else {
        fprintf(stderr, "Failed to connect \n");
    }


    char *line = NULL;
    size_t lineSize =0;
    printf("type what you want to be send (EXIT to exit)\n");

    while (true) {
        size_t charCount = getline(&line, &lineSize, stdin);

        if(charCount >0){
            if(strcmp(line, "EXIT\n") == 0){
                break;
            }
            size_t amountWasSend = send(socketFD, line, charCount, 0);
            // write()
        }

    }

    // char* message;

    // message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";

    // send(socketFD, message, strlen(message), 0);
    // // write()

    // char buffer[1024];
    // recv(socketFD, buffer, 1024, 0);
    // // fansy read()

    // printf("Responce: %s \n", buffer);

    close(socketFD);


    return 0;
}
