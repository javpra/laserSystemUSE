#ifndef LASERSYSTEMCLIENT_H
#define LASERSYSTEMCLIENT_H
#include <thread>



class laserSystemClient
{
public:
    laserSystemClient(const char *SERVER);
    struct positionData{
        float timestamp;
        float x;
        float y;
        float z;
    };
    std::thread measThread;
    positionData getData();
    void dataReceiveThread();
};

#endif // LASERSYSTEMCLIENT_H
