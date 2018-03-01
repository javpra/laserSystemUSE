#include "lasersystemclient.h"
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <thread>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define PORT 2018   //The port on which to listen for incoming data

struct sockaddr_in si_other;
int s, slen=sizeof(si_other);
WSADATA wsa;
laserSystemClient::positionData d;

void laserSystemClient::dataReceiveThread(){
    //start communication
    while(1)
    {
        if (recvfrom(s, (char*)&d, sizeof(laserSystemClient::positionData), 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }
    }
    closesocket(s);
    WSACleanup();
}

laserSystemClient::positionData laserSystemClient::getData(){
    return d;
}

laserSystemClient::laserSystemClient(const char* SERVER)
{
    char message[] = "handshake";
    //Initialise winsock
    printf("Initialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");

    //create socket
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
    {
        printf("socket() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    //setup address structure
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);


    ///**************************************************************************************************************// DESCOMENTAR
    /// SEND HANDSHAKE
    if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    ///**************************************************************************************************************//

    measThread = std::thread (&laserSystemClient::dataReceiveThread,this);


}


