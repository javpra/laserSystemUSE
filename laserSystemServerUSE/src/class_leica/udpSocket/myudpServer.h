//Base class QObject

#include<stdio.h>
#include<WinSock2.h>
#include<iostream>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 512  //Max length of buffer
#define PORT 2018   //The port on which to listen for incoming data
 
class MyUDPServer
{
public:
    MyUDPServer();
    //*************** SERVER ************************//
    void connectSocket(SOCKET &s, sockaddr_in &si_other, int &slen);
private:


};
