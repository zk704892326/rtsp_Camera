#include "largemotor.h"
#include <arpa/inet.h>
#include <iostream>
using namespace std;

LargeMotor::LargeMotor()
{
    isConnected = false;
    cmdAckLen = 0;
    this->MotorLeft = 0;
    this->MotorRight = 0;
    this->MotorUp1 = 0;
    this->MotorUp2 = 0;
    timeout = QDateTime::currentDateTime();
    connect(&tcpsocket, SIGNAL(connected()), this, SLOT(connectedHandle()));
    connect(&tcpsocket, SIGNAL(readyRead()), this, SLOT(readHandle()));
    connect(&tcpsocket, SIGNAL(disconnected()), this, SLOT(disconnectHandle()));
    connect(&tcpsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorHandle(QAbstractSocket::SocketError)));
}

void LargeMotor::connectedHandle() {
    isConnected = true;
    cout<<"connectedHandle"<<endl;
}

bool LargeMotor::open(QString hostName, quint16 port) {
    if(0 == this->hostName.compare(hostName) && this->port == port) {
        return true;
    }
    this->hostName = hostName;
    this->port = port;
    tcpsocket.close();
    isConnected = false;
    return true;
}

bool LargeMotor::__connect() {
    tcpsocket.connectToHost(hostName, port);
    bool connected = tcpsocket.waitForConnected();
    qDebug()<<"connected"<<connected;
    return true;
}

void LargeMotor::readHandle() {
    QDateTime time0 = QDateTime::currentDateTime();
    qint64 len = tcpsocket.bytesAvailable();
    if(len <= 0) {
        cout<<"len <= 0"<<endl;
        return;
    }
    if(time0 > timeout) {
        cmdAckLen = 0;
        timeout = time0.addMSecs(500);
        cout<<"time0 > timeout"<<endl;
    }
    if(cmdAckLen + len > sizeof(MotorCmdAck)) {
        len = sizeof(MotorCmdAck) - cmdAckLen;
        cout<<"cmdAckLen + len > sizeof(MotorCmdAck)"<<endl;
    }
    char *data = (char *)&cmdAck;
    len = tcpsocket.read(data + cmdAckLen, len);
    if(len > 0) {
        cmdAckLen += len;
        QByteArray byte;
        byte = QByteArray(data);
        //qDebug() << byte.toHex().toStdString().c_str();
    }
    if(cmdAckLen < sizeof(MotorCmdAck)) {
        cout<<"cmdAckLen < sizeof(MotorCmdAck)"<<endl;
        return;
    }
    quint8 *data1 = (quint8 *)data;
    quint8 *sum1 = data1 + (sizeof(MotorCmdAck) - 1);
    quint8 sum0 = 0;
    data1 = data1 + 4;
    for(;data1 != sum1;++data1) {
        sum0 += *data1;
    }
    if(sum0 != *sum1) {
        cout<<"sum0 != *sum1"<<" "<<int(sum0)<<" "<<int(*sum1)<<endl;
    }
   QString label = "";//QString::asprintf("%d %u, %d %u, %d %u, %d %u",
   //             cmdAck.cmds[0].step, cmdAck.cmds[0].result,
   //             cmdAck.cmds[1].step, cmdAck.cmds[1].result,
   //             cmdAck.cmds[2].step, cmdAck.cmds[2].result,
   //             cmdAck.cmds[3].step, cmdAck.cmds[3].result
   //         );
    if((cmdAck.cmds[0].result != 4)){
       this->MotorLeft = cmdAck.cmds[0].step;
    }else if(cmdAck.cmds[0].result == 4)
    {
       this->MotorLeft = cmdAck.cmds[0].step;
       this->MotorLeftAll = cmdAck.cmds[0].step;
    }
    if((cmdAck.cmds[1].result != 4)){
       this->MotorRight = cmdAck.cmds[1].step;
    }else if(cmdAck.cmds[1].result == 4)
    {
        this->MotorRight = cmdAck.cmds[1].step;
        this->MotorRightAll = cmdAck.cmds[1].step;
    }
    if((cmdAck.cmds[2].result != 4)){
       this->MotorUp1 = cmdAck.cmds[2].step;
    }else if(cmdAck.cmds[2].result == 4)
    {
       this->MotorUp1 = cmdAck.cmds[2].step;
       this->MotorUp1All = cmdAck.cmds[2].step;
    }
    if((cmdAck.cmds[3].result != 4)){
       this->MotorUp2 = cmdAck.cmds[3].step;
    }else if(cmdAck.cmds[3].result == 4){
       this->MotorUp2 = cmdAck.cmds[3].step;
       this->MotorUp2All = cmdAck.cmds[3].step;
    }


    emit changeMotorState(label,cmdAck.cmds[0].step,cmdAck.cmds[1].step,cmdAck.cmds[2].step,cmdAck.cmds[3].step);



    cout<<"readHandle "<<label.toStdString().c_str()<<endl;
    cmdAckLen = 0;
}

void LargeMotor::errorHandle(QAbstractSocket::SocketError) {
    cout<<"errorHandle "<<tcpsocket.errorString().toStdString().c_str()<<endl;
}

void LargeMotor::disconnectHandle() {
    tcpsocket.close();
    isConnected = false;
    cout<<"disconnectHandle"<<endl;
}

bool LargeMotor::m1Left(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[0].step = htonl(MOTOR_CMD_STEP);
    cmd.cmds[0].cmd = MOTOR_CMD_MOVE;
    cmd.cmds[0].speed = MOTOR_CMD_SPEED;

    cmd.cmds[1].cmd = MOTOR_CMD_NULL;
    cmd.cmds[2].cmd = MOTOR_CMD_NULL;
    cmd.cmds[3].cmd = MOTOR_CMD_NULL;
    return sendData();
}

bool LargeMotor::m1Right(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[0].step = htonl(-MOTOR_CMD_STEP);
    cmd.cmds[0].cmd = MOTOR_CMD_MOVE;
    cmd.cmds[0].speed = MOTOR_CMD_SPEED;

    cmd.cmds[1].cmd = MOTOR_CMD_NULL;
    cmd.cmds[2].cmd = MOTOR_CMD_NULL;
    cmd.cmds[3].cmd = MOTOR_CMD_NULL;
    return sendData();
}

bool LargeMotor::m2Left(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[1].step = htonl(MOTOR_CMD_STEP);
    cmd.cmds[1].cmd = MOTOR_CMD_MOVE;
    cmd.cmds[1].speed = MOTOR_CMD_SPEED;

    cmd.cmds[0].cmd = MOTOR_CMD_NULL;
    cmd.cmds[2].cmd = MOTOR_CMD_NULL;
    cmd.cmds[3].cmd = MOTOR_CMD_NULL;
    return sendData();
}

bool LargeMotor::m2Right(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[1].step = htonl(-MOTOR_CMD_STEP);
    cmd.cmds[1].cmd = MOTOR_CMD_MOVE;
    cmd.cmds[1].speed = MOTOR_CMD_SPEED;

    cmd.cmds[0].cmd = MOTOR_CMD_NULL;
    cmd.cmds[2].cmd = MOTOR_CMD_NULL;
    cmd.cmds[3].cmd = MOTOR_CMD_NULL;
    return sendData();
}

bool LargeMotor::m3Left(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[2].step = htonl(MOTOR_CMD_STEP);
    cmd.cmds[2].cmd = MOTOR_CMD_MOVE;
    cmd.cmds[2].speed = MOTOR_CMD_SPEED;

    cmd.cmds[0].cmd = MOTOR_CMD_NULL;
    cmd.cmds[1].cmd = MOTOR_CMD_NULL;
    cmd.cmds[3].cmd = MOTOR_CMD_NULL;
    return sendData();
}

bool LargeMotor::m3Right(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[2].step = htonl(-MOTOR_CMD_STEP);
    cmd.cmds[2].cmd = MOTOR_CMD_MOVE;
    cmd.cmds[2].speed = MOTOR_CMD_SPEED;

    cmd.cmds[0].cmd = MOTOR_CMD_NULL;
    cmd.cmds[1].cmd = MOTOR_CMD_NULL;
    cmd.cmds[3].cmd = MOTOR_CMD_NULL;
    return sendData();
}

bool LargeMotor::m4Left(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[3].step = htonl(MOTOR_CMD_STEP);
    cmd.cmds[3].cmd = MOTOR_CMD_MOVE;
    cmd.cmds[3].speed = MOTOR_CMD_SPEED;

    cmd.cmds[0].cmd = MOTOR_CMD_NULL;
    cmd.cmds[1].cmd = MOTOR_CMD_NULL;
    cmd.cmds[2].cmd = MOTOR_CMD_NULL;
    return sendData();
}

bool LargeMotor::m4Right(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[3].step = htonl(-MOTOR_CMD_STEP);
    cmd.cmds[3].cmd = MOTOR_CMD_MOVE;
    cmd.cmds[3].speed = MOTOR_CMD_SPEED;

    cmd.cmds[0].cmd = MOTOR_CMD_NULL;
    cmd.cmds[1].cmd = MOTOR_CMD_NULL;
    cmd.cmds[2].cmd = MOTOR_CMD_NULL;
    return sendData();
}

bool LargeMotor::mnStop(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[0].cmd = MOTOR_CMD_STOP;
    cmd.cmds[1].cmd = MOTOR_CMD_STOP;
    cmd.cmds[2].cmd = MOTOR_CMD_STOP;
    cmd.cmds[3].cmd = MOTOR_CMD_STOP;
    return sendData();
}

bool LargeMotor::mnReset1(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[0].step = 0;
    cmd.cmds[1].step = 0;
    cmd.cmds[2].step = 0;
    cmd.cmds[3].step = 0;

    cmd.cmds[0].cmd = MOTOR_CMD_RESET;
    cmd.cmds[1].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;
    cmd.cmds[2].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;
    cmd.cmds[3].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;

    cmd.cmds[0].speed = MOTOR_CMD_SPEED;
    cmd.cmds[1].speed = MOTOR_CMD_SPEED;
    cmd.cmds[2].speed = MOTOR_CMD_SPEED;
    cmd.cmds[3].speed = MOTOR_CMD_SPEED;

    return sendData();
}

bool LargeMotor::mnReset2(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[0].step = 0;
    cmd.cmds[1].step = 0;
    cmd.cmds[2].step = 0;
    cmd.cmds[3].step = 0;

    cmd.cmds[0].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;
    cmd.cmds[1].cmd = MOTOR_CMD_RESET;
    cmd.cmds[2].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;
    cmd.cmds[3].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;

    cmd.cmds[0].speed = MOTOR_CMD_SPEED;
    cmd.cmds[1].speed = MOTOR_CMD_SPEED;
    cmd.cmds[2].speed = MOTOR_CMD_SPEED;
    cmd.cmds[3].speed = MOTOR_CMD_SPEED;

    return sendData();
}

bool LargeMotor::mnGoto(qint32 a,qint32 b,qint32 c,qint32 d,QString hostName, quint16 port) {


    qDebug() << hostName ;
    this->open(hostName, port);
    qDebug() << "guozhixin Open ";
    prepareData();
    cmd.cmds[0].step = a;
    cmd.cmds[1].step = b;
    cmd.cmds[2].step = c;
    cmd.cmds[3].step = d;

    cmd.cmds[0].cmd = MOTOR_CMD_GOTO;
    cmd.cmds[1].cmd = MOTOR_CMD_GOTO;
    cmd.cmds[2].cmd = MOTOR_CMD_GOTO;
    cmd.cmds[3].cmd = MOTOR_CMD_GOTO;

    cmd.cmds[0].speed = MOTOR_CMD_SPEED;
    cmd.cmds[1].speed = MOTOR_CMD_SPEED;
    cmd.cmds[2].speed = MOTOR_CMD_SPEED;
    cmd.cmds[3].speed = MOTOR_CMD_SPEED;

    return sendData();
}

bool LargeMotor::mnReset3(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[0].step = 0;
    cmd.cmds[1].step = 0;
    cmd.cmds[2].step = 0;
    cmd.cmds[3].step = 0;

    cmd.cmds[0].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;
    cmd.cmds[1].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;
    cmd.cmds[2].cmd = MOTOR_CMD_RESET;
    cmd.cmds[3].cmd = MOTOR_CMD_RESET;

    cmd.cmds[0].speed = MOTOR_CMD_SPEED;
    cmd.cmds[1].speed = MOTOR_CMD_SPEED;
    cmd.cmds[2].speed = MOTOR_CMD_SPEED;
    cmd.cmds[3].speed = MOTOR_CMD_SPEED;

    return sendData();
}

bool LargeMotor::mnReset4(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[0].step = 0;
    cmd.cmds[1].step = 0;
    cmd.cmds[2].step = 0;
    cmd.cmds[3].step = 0;

    cmd.cmds[0].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;
    cmd.cmds[1].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;
    cmd.cmds[2].cmd = /*MOTOR_CMD_RESET*/MOTOR_CMD_NULL;
    cmd.cmds[3].cmd = MOTOR_CMD_RESET;

    cmd.cmds[0].speed = MOTOR_CMD_SPEED;
    cmd.cmds[1].speed = MOTOR_CMD_SPEED;
    cmd.cmds[2].speed = MOTOR_CMD_SPEED;
    cmd.cmds[3].speed = MOTOR_CMD_SPEED;

    return sendData();
}

bool LargeMotor::mnResetAll(QString hostName, quint16 port) {
    this->open(hostName, port);
    prepareData();
    cmd.cmds[0].step = 0;
    cmd.cmds[1].step = 0;
    cmd.cmds[2].step = 0;
    cmd.cmds[3].step = 0;

    cmd.cmds[0].cmd = MOTOR_CMD_RESET;
    cmd.cmds[1].cmd = MOTOR_CMD_RESET;
    cmd.cmds[2].cmd = MOTOR_CMD_RESET;
    cmd.cmds[3].cmd = MOTOR_CMD_RESET;

    cmd.cmds[0].speed = MOTOR_CMD_SPEED;
    cmd.cmds[1].speed = MOTOR_CMD_SPEED;
    cmd.cmds[2].speed = MOTOR_CMD_SPEED;
    cmd.cmds[3].speed = MOTOR_CMD_SPEED;

    return sendData();
}

void LargeMotor::prepareData() {
    memset(&cmd, 0, sizeof(MotorCmd));
    memcpy(cmd.head, MOTOR_CMD_HEAD, strlen(MOTOR_CMD_HEAD));
    cmd.series = 0;
}

bool LargeMotor::sendData() {
    if(!isConnected) {
        __connect();
    }
    quint8 *data = (quint8 *)&cmd;
    quint8 *sum = data + (sizeof(MotorCmd) - 1);
    data = data+4;
    for(;data != sum;++data) {
        *sum += *data;
    }

    QByteArray cstr((char *)&cmd,sizeof(MotorCmd));

    //qDebug() << cstr.toHex().toStdString().c_str();

    tcpsocket.write((const char *)&cmd, sizeof(MotorCmd));
//    tcpsocket.waitForBytesWritten();
    tcpsocket.flush();
    return true;
}
