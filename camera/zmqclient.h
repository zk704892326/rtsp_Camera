#ifndef ZMQCLIENT_H
#define ZMQCLIENT_H

#include <QThread>
#include <zmq.h>

union test_short
{
  short office;
  char teacher[2];
};

union test_num
{
  int office;
  char teacher[4];
};

typedef struct sendData {
    unsigned char a1;
    unsigned char a2;//cmd
    short a3;//x car1 f r
    short a4;
    short a5;//turn
    short a6;//shift x,y
    short a7;//shift f,r
    short a8;//up,down
    unsigned char a9;
    unsigned char a10;
}__attribute__ ((packed)) sendData_t;

typedef struct recvData {
    unsigned char head;
    unsigned char len;
    test_short Xz;
    test_short Yz;
    test_short Zz;
    test_short Az;
    test_short Bz;
    test_short Cz;
    test_num RFID;
    test_short active;
    unsigned char state;
    test_short CS1;
    test_short CS2;
    test_short CS3;
    test_short CS4;
    test_short CS5;
    test_short CS6;
    test_short CS7;
    test_short CS8;
    unsigned char a19;
}__attribute__ ((packed)) recvData_t;

class zmqClient : public QThread
{
public:
    int Xl;
    int Yl;
    int Zl;
    int Al;
    int Bl;
    int Cl;
    char Xx1,Xx2;
    char Yx1,Yx2;
    char Zx1,Zx2;
    char Ax1,Ax2;
    char Bx1,Bx2;
    char Cx1,Cx2;
    char Xs,Ys,Zs,As,Bs,Cs;
    //char inits;
    //char StaticBu;
    int CarDNum,isCarNumChange;//RFID change
    int CameraX,CameraY;//Camera XY
    int Car_Number; //1 or 2 che
    int CarStation; //car status 1. normal 2. goback 3. stop 0.No
    void * pCtx = NULL;
    void * pSock = NULL;
    explicit zmqClient();
    ~zmqClient();
    int ConnectServer(const char *pAddr,int CarNumber);
    void disconnect();
    void sendText(char *str,const int len);
private:
     void run();
};

#endif // ZMQCLIENT_H
