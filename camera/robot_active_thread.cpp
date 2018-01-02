#include "robot_active_thread.h"
#include "zmqclient.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <QTime>

Robot_Active_Thread::Robot_Active_Thread()
{
    this->CameraRun = 0;
    this->isStatas1 = 0;
    this->isStatas2 = 0;

    this->currentPointx = 0;
    this->currentPointy = 0;
}

Robot_Active_Thread::~Robot_Active_Thread()
{

}

void Robot_Active_Thread::sendOneText(char cmd,int a,int Num)
{
    printf("%s Z S\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = cmd;
    abc.a2 = 16;
    if(a == 1){
       abc.a3 = Num;
    }else{
        abc.a3 = 0;
    }
    if(a == 2){
       abc.a4 = Num;
    }else{
        abc.a4 = 0;
    }
    if(a == 3){
       abc.a5 = Num;
    }else{
        abc.a5 = 0;
    }
    if(a == 4){
       abc.a6 = Num;
    }else{
        abc.a6 = 0;
    }
    if(a == 5){
       abc.a7 = Num;
    }else{
        abc.a7 = 0;
    }
    if(a == 6){
       abc.a8 = Num;
    }else{
        abc.a8 = 0;
    }
    abc.a9 = this->zmqClientOne.CameraX;
    abc.a10 = this->zmqClientOne.CameraY;

    //abc.a9 = 0;
    //abc.a10 = 0;

    this->zmqClientOne.sendText((char *)(&abc),16);
}

void Robot_Active_Thread::sendTwoText(char cmd,int a,int Num)
{
    printf("%s Z S\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = cmd;
    abc.a2 = 16;
    if(a == 1){
       abc.a3 = Num;
    }else{
        abc.a3 = 0;
    }
    abc.a4 = 0;
    if(a == 3){
       abc.a5 = Num;
    }else{
        abc.a5 = 0;
    }
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = 0;
    abc.a10 = 0;

    this->zmqClientTwo.sendText((char *)(&abc),16);
}
void Robot_Active_Thread::smallcaraction()
{
    this->zmqClientOne.isCarNumChange = 0;
    this->sendOneText(1,1,0);
    sleep(1);
    this->zmqClientOne.CameraX=0;
    this->zmqClientOne.CameraY=90;
     this->sendOneText(1,CAMERA_LEFT_RIGHT_DIRECTION,45);
    sleep(2);
    this->sendOneText(1,CAR1_TURN_DIRECTION,1);
    sleep(10);
    this->zmqClientOne.CameraY=80;
     this->sendOneText(1,CAMERA_LEFT_RIGHT_DIRECTION,52);
    sleep(2);
    this->sendOneText(1,CAR_UP_DOWN_DIRECTION,20);
    sleep(20);
    this->zmqClientOne.CameraX=0;
    this->zmqClientOne.CameraY=0;
    this->sendOneText(1,CAMERA_LEFT_RIGHT_DIRECTION,0);
    sleep(3);
    this->sendOneText(1,CAR1_TURN_DIRECTION,-5);
    sleep(30);
    this->sendOneText(1,CAR_UP_DOWN_DIRECTION,-20);
    sleep(20);
    this->sendOneText(1,CAR1_TURN_DIRECTION,4);
    sleep(25);

    this->sendOneText(1,1,-2000);

}

void Robot_Active_Thread::CarResultInsert()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_PATH);
    if(!db.open()) {
        //qDebug()<<db.lastError();
    } else {
//      qDebug()<<"db open success";
    }

    QDateTime date0 = QDateTime::currentDateTime();
    QSqlQuery query;
    query.prepare("INSERT INTO records (time, point, state, img_path) VALUES (:time, :point, :state, :img_path);");
    query.bindValue(0, date0.toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(1, "");
    query.bindValue(2, "ok");
    query.bindValue(3, "record.png");
    if(!query.exec()) {
        //qDebug()<<db.lastError();
    }
    db.commit();
    db.close();
}

void Robot_Active_Thread::Car1Active()
{
    if((this->zmqClientOne.isCarNumChange == 1)&&(this->zmqClientTwo.CarStation ==1)){

        if((this->zmqClientOne.CarDNum == 0xDBD6D795)&&(this->zmqClientOne.CarStation == 1)){

            smallcaraction();
        }

        if((this->zmqClientOne.CarDNum == 0xE9AB5449)&&(this->zmqClientOne.CarStation == 1)){
            this->zmqClientOne.isCarNumChange = 0;
            this->sendOneText(1,1,0);
            sleep(2);
            smallcaraction();
            this->sendOneText(1,1,-2000);
            //this->sendOneText(1,3,200);
            //this->isStatas1 = 3;
            //sleep(40);

        }
    }

    if(this->isStatas1 > 0){
//               if((this->zmqClientOne.Cx2 == 0)&&(this->isStatas1 == 1)){
//                   this->sendOneText(1,6,-2000);
//                   this->isStatas1 = 2;
//               }
//               if((this->zmqClientOne.Cx1 == 0)&&(this->isStatas1 == 2)){
//                   this->isStatas1 = 0;
//                   this->sendOneText(1,1,-2000);
//               }
       if(this->isStatas1 == 3){
//           this->sendOneText(1,3,-200);
//           sleep(40);
//           this->sendOneText(1,1,-2000);
           this->isStatas1 = 0;
       }
       if(this->isStatas1 == 1){
//           this->sendOneText(1,3,200);
//           sleep(40);
//           this->sendOneText(1,1,-2000);
           this->isStatas1 = 0;
       }
    }
}

void Robot_Active_Thread::Car2Active()
{
    if(this->zmqClientTwo.isCarNumChange == 1){

        if(this->zmqClientTwo.CarDNum == 0xE9ABA49C)/*&&(this->zmqClientOne.Xx1 == 0)*/{
            if(this->zmqClientTwo.CarStation == 1){
                this->zmqClientTwo.isCarNumChange = 0;
                this->sendTwoText(1,1,0);
                sleep(1);
                this->sendOneText(1,1,0);
                sleep(1);
                this->sendTwoText(1,3,-10);
                sleep(20);
                this->sendOneText(1,1,2000);
                this->isStatas2 = 1;
                this->zmqClientOne.CarStation = 1;
                sleep(10);
            }else{
                printf("this->zmqClientTwo.CarStation  %d  \n",this->zmqClientTwo.CarStation);
            }
        }

        if((this->zmqClientTwo.CarDNum == 0xDBD6DDFB)||(this->zmqClientTwo.CarDNum == 0xDFD6DDFB)/*&&(this->zmqClientOne.Xx1 == 0)*/){
            if((this->zmqClientTwo.CarStation == 1)){
                this->zmqClientTwo.isCarNumChange = 0;
                this->sendTwoText(1,1,0);
                sleep(1);
                this->sendOneText(1,1,0);
                sleep(1);
                this->sendTwoText(1,3,-10);
                sleep(20);
                this->sendOneText(1,1,2000);
                this->isStatas2 = 1;
                this->zmqClientOne.CarStation = 1;
                sleep(10);
            }else{
                printf("this->zmqClientTwo.CarStation  %d  \n",this->zmqClientTwo.CarStation);
            }
        }

        if(((this->zmqClientTwo.CarDNum == 0xDBD8DA6D)||(this->zmqClientTwo.CarDNum == 0xE9ACA242))/*&&(this->zmqClientOne.Xx1 == 0)*/&&(this->zmqClientTwo.CarStation == 2)){
            this->zmqClientTwo.isCarNumChange = 0;
            this->sendTwoText(1,1,0);
            this->zmqClientTwo.CarStation = 0;
        }

        //77B73B5B

        if((this->zmqClientTwo.CarDNum == 0xEDACB6CB)||(this->zmqClientTwo.CarDNum == 0xE9ACB6CB)||(this->zmqClientTwo.CarDNum == 0xD58FD055)/*&&(this->zmqClientOne.Xx1 == 0)*/){
            if(this->zmqClientTwo.CarStation == 1){
                this->zmqClientTwo.isCarNumChange = 0;
                this->sendTwoText(1,1,0);
                sleep(2);
                this->sendTwoText(1,1,-2000);
                this->zmqClientTwo.CarStation = 2;
            }else{
                printf("this->zmqClientTwo.CarStation  %d  \n",this->zmqClientTwo.CarStation);
            }
        }

        //Stop

        //goback

    }
    if(this->isStatas2 > 0){
        if((this->zmqClientOne.Xx1 == 0)&&(this->isStatas2 == 1)){
            sleep(1);
            this->sendTwoText(1,3,10);
            sleep(25);
            this->isStatas2 = 0;
            this->sendTwoText(1,1,1000);

        }
    }
}

void Robot_Active_Thread::run(){
    while(1){

        if(this->CameraRun == 1){

            Car1Active();
            Car2Active();

        }

        this->currentPointx++;
        this->currentPointy++;

        msleep(50);
    }
}
