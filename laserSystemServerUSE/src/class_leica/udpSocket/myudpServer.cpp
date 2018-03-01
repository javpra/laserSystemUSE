#include "myudpServer.h"
 
MyUDPServer::MyUDPServer()
{


}
void MyUDPServer::connectSocket(SOCKET &s, sockaddr_in &si_other, int &slen){
    struct sockaddr_in server;
    int recv_len;
    char buf[BUFLEN];
    WSADATA wsa;

    slen = sizeof(si_other) ;

    //Initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP )) == INVALID_SOCKET){
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );

    //Bind
    if(bind(s,(struct sockaddr *)&server,sizeof(server)) == SOCKET_ERROR)
        {
            printf("Bind failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }
    puts("Bind done");

    printf("Waiting for handshake data...\n");
    fflush(stdout);



    //clear the buffer by filling null, it might have previously received data
    memset(buf,'\0', BUFLEN);

    //try to receive some data, this is a blocking call
    if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR){
        printf("recvfrom() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
}






