#ifndef ROBOT_ACTIVE_THREAD_H
#define ROBOT_ACTIVE_THREAD_H
#include "zmqclient.h"
#define CAR_RAIL_DIRECTION 1
#define CAR_RAILCROSS_DIRECTION 2
#define CAR2_UP_DOWN_DIRECTION 3
#define CAR1_TURN_DIRECTION 3
#define CAR_SHIFT_DIRECTION 4
#define CAR_SHIFTCROSS_DIRECTION 5
#define CAR_UP_DOWN_DIRECTION 6
#define CAMERA_UP_DOWN_DIRECTION 7
#define CAMERA_LEFT_RIGHT_DIRECTION 8

#define DB_PATH   "camera.db"

class Robot_Active_Thread : public QThread
{
public:
    quint32 currentPointx; //map X
    quint32 currentPointy; //map Y
    int CameraRun;  //func active
    int isStatas1,isStatas2; // 1,2 car status
    zmqClient zmqClientOne;
    zmqClient zmqClientTwo;
    void smallcaraction();
    void sendOneText(char cmd,int a,int Num);
    void sendTwoText(char cmd,int a,int Num);
    explicit Robot_Active_Thread();
    ~Robot_Active_Thread();
    void CarResultInsert();
    void Car1Active();
    void Car2Active();
private:
    void run();

};

#endif // ROBOT_ACTIVE_THREAD_H
