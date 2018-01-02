#ifndef ELE_MACH_H
#define ELE_MACH_H

#include <QObject>
#include "largemotor.h"
//#include "motor/motor.h"
#include <QString>

class Ele_mach : public QObject
{
    Q_OBJECT
public:
    explicit Ele_mach(QObject *parent = 0);
    int set_Camera_config(QString host,qint16 port);
    int send_message_to_Mach(int left,int right,int up1,int up2,float cameraleft,float cameraright,float cameraZone,int cameraDirection,QString host,qint16 port);
    LargeMotor largeMotor;
    //Motor motor;
    int Eleft;
    int Eright;
    int Eup1;
    int Eup2;
    int cameraleft;
    int cameraright;
    QString cameraHost;
    qint16 cameraPort;

signals:

public slots:
};

#endif // ELE_MACH_H
