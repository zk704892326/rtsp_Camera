#include "ele_mach.h"
#include "largemotor.h"
#include <QThread>
#include <unistd.h>
#include <QString>
//#include "motor/motor.h"

Ele_mach::Ele_mach(QObject *parent) : QObject(parent)
{
    this->Eleft = 0;this->Eright = 0;
    this->Eup1 = 0;this->Eup2 = 0;
    //this->largeMotor = NULL;

}

int Ele_mach::set_Camera_config(QString host,qint16 port)
{
    this->cameraHost = host;
    this->cameraPort = port;
}

int Ele_mach::send_message_to_Mach(int left,int right,int up1,int up2,float cameraleft,float cameraright,float cameraZone,int cameraDirection,QString host,qint16 port)
{
    this->Eleft = left;
    this->Eright = right;
    this->Eup1 = up1;
    this->Eup2 = up2;

    int AllNum = 0;

    qDebug()<<"abcdeferre"<<host<<"  ";

    //if(this->largeMotor.){
        //this->largeMotor.mnStop(host,port);

        //QCoreApplication::processEvents(QEventLoop::AllEvents, 100000000);

        //this->largeMotor.mnGoto(this->largeMotor.MotorLeft,this->largeMotor.MotorRight,0,0,host,port);
        //this->largeMotor.m1Left(host,port);

        //while(1){
        //    if(
        //            (0 == this->largeMotor.MotorUp1)&&
        //            (0 == this->largeMotor.MotorUp2)){
        //        break;
        //    }else{
        //        QCoreApplication::processEvents(QEventLoop::AllEvents, 100000);
        //    }
        //}

        //this->largeMotor.mnGoto(left,right,0,0,host,port);
        //this->largeMotor.m1Left(host,port);

        //while(1){
        //    if((this->Eleft ==this->largeMotor.MotorLeft)&&
        //            (this->Eright == this->largeMotor.MotorRight)
        //      ){
        //        break;
        //    }else{
         //       QCoreApplication::processEvents(QEventLoop::AllEvents, 1000000);
                //AllNum++;
                //if(AllNum > 100){
                //    AllNum = 0;
                //   this->largeMotor.mnGoto(left,right,up1,up2,host,port);
                //}
           // }
        //}

        this->largeMotor.mnGoto(left,right,up1,up2,host,port);
        //this->largeMotor.m1Left(host,port);

        while(1){
            if((this->Eleft ==this->largeMotor.MotorLeft)&&
                    (this->Eright == this->largeMotor.MotorRight)&&
                    (this->Eup1 == this->largeMotor.MotorUp1)&&
                    (this->Eup2 == this->largeMotor.MotorUp2)){
                break;
            }else{
                sleep(1);
                QCoreApplication::processEvents(QEventLoop::AllEvents, 1000000);
                AllNum++;
                if(AllNum > 2){
                    AllNum = 0;
                   this->largeMotor.mnGoto(left,right,up1,up2,host,port);
                }
            }
        }


        //if(!motor.isOpen()) {
        //    motor.open(this->cameraHost.toStdString().c_str(), this->cameraPort, "admin", "admin");
        //}
        //motor.rotateSetPostion(cameraDirection,cameraleft,cameraright,cameraZone);
        //qDebug()<<cameraleft<<"  "<<cameraright<<"  "<<cameraDirection<<"  "<<cameraZone<<endl;


    //}
}
