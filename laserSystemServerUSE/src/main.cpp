#include <iostream>
#include <thread>
#include <class_leica/geocom_class_leica.h>
#include <iomanip>                   //sirve para poder establecer la precision de std::cout
#include <stdio.h>
#include <errno.h>
#include <vector>
#include <class_leica/udpSocket/myudpServer.h>

GeoCom_Class_Leica leica;
bool finishThread = false;
float x,y,z,measureTime;
struct datos{
    float timestamp;
    float x;
    float y;
    float z;
}d;

SOCKET s;
struct sockaddr_in si_other;
int slen;
MyUDPServer udpServer;


/******************************************************************************************************************************************************************************/
/*                                                                    continuousMeaThread                                                                                     */
/******************************************************************************************************************************************************************************/

void continuousMeaThread()
{
    while (finishThread==false) { //Press 1
        std::vector<std::string> coordinateMea;
        coordinateMea = leica.TMC_GetCoordinate(1000,1);
        if (stod(coordinateMea[0])==0 || stod(coordinateMea[0])==1284){
            d = {stof(coordinateMea[4]),stof(coordinateMea[1]),stof(coordinateMea[2]),stof(coordinateMea[3])};
            ///**************************************************/
            if (sendto(s, (char*)&d, sizeof(datos), 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR){
                    printf("sendto() failed with error code : %d" , WSAGetLastError());
                    exit(EXIT_FAILURE);
                }
            ///**************************************************/
        }
        else if(stod(coordinateMea[0])==1285){
            std::cout << "Angle values okay, but no valid distance" << std::endl;
        }
        else{
            std::cout << "Measurement error: " << coordinateMea[0] << std::endl;
        }
    }
}

/******************************************************************************************************************************************************************************/
/*                                                                           MAIN                                                                                             */
/******************************************************************************************************************************************************************************/

int main(int argc, char* argv[])
{
    udpServer.connectSocket(s,si_other,slen);

    if(leica.connectSocket(1212,"192.168.254.3")==false){
        std::cout << "Connection to TS Leica failed" << std::endl;
        return 0;
    }

    std::cout << "Connection to TS Leica successful" << std::endl;

    leica.initTotalStation();
    char input[1000];


    bool fin=false;
    while(fin==false)
    {
        std::cout << "\n****************************OPERATIONS MENU****************************" << std::endl;
        std::cout << "- Press 1 to measure flight trajectory." << std::endl;
        std::cout << "- Press 2 to take one simple measurement." << std::endl;
        std::cout << "- Press 3 to visualize last measure point." << std::endl;
        std::cout << "- Press 4 to EXIT." << std::endl;
        std::cin.getline(input,1000);
        if(1){
            switch (*input) // Different replys for the menu
            {
                case '1':
                {
                    finishThread=false;
                    std::thread measThread (continuousMeaThread);
                    std::cout << "\nMeasuring trajectory..." << std::endl;
                    std::cout << "\nPress F to finish measure" << std::endl;
                    while(finishThread==false)
                    {
                        std::cin.getline(input,1000);
                        if ((*input=='f' || *input=='F') && strlen(input)==1){
                            finishThread = true;
                            measThread.join();
                        }
                        else {
                            std::cout << "\nERROR. That is not the F letter. Try again" << std::endl;
                        }
                    }
                    break;
                }
                case '2' :
                {
                    std::vector<std::string> coordinateMea;
                    coordinateMea = leica.TMC_GetCoordinate(100,1);
                    d = {stof(coordinateMea[4]),stof(coordinateMea[1]),stof(coordinateMea[2]),stof(coordinateMea[3])};
                    std::cout << std::setprecision(10) << "\nVisualizing measured point...\n" << "X: " << d.x << "\nY: " << d.y << "\nZ: " << d.z << "\nMeasure Time: " << d.timestamp << std::endl;
                    break;
                }
                case '3' :
                {
                    std::cout << std::setprecision(10) << "\nVisualizing last measured point...\n" << "X: " << d.x << "\nY: " << d.y << "\nZ: " << d.z << "\nMeasure Time: " << d.timestamp <<std::endl;
                    break;
                }
                case '4':
                {
                    std::cout << "\nEXIT..." << std::endl;
                    fin = true;
                    break;
                }
                default:
                {
                    std::cout << "\nERROR. That is not a number of the menu. Try again" << std::endl;
                    break;
                }
            }
        }
        else {
            std::cout << "\nERROR. That is not a number of the menu. Try again" << std::endl;
        }
    }

    return 0;
}
