#ifndef LARGEMOTOR_H
#define LARGEMOTOR_H

#include <QObject>
#include <QtNetwork>

#define MOTOR_CMD_HEAD      "EMMA"
#define MOTOR_CMD_STEP      5
#define MOTOR_CMD_MOVE      1
#define MOTOR_CMD_STOP      2
#define MOTOR_CMD_GOTO      3
#define MOTOR_CMD_RESET     4
#define MOTOR_CMD_SPEED     1
#define MOTOR_CMD_NULL      0

typedef struct MotorCmd {
    char head[4];
    quint8 series;
    struct {
        qint32 step;
        quint8 cmd;
        quint8 speed;
    } __attribute__ ((packed)) cmds[4];
    quint8 reset;
    quint8 sum;
} __attribute__ ((packed)) MotorCmd;

typedef struct MotorCmdAck {
    char head[4];
    quint8 series;
    struct {
        qint32 step;
        quint8 result;
    } __attribute__ ((packed)) cmds[4];
    quint8 reset;
    quint8 sum;
} __attribute__ ((packed)) MotorCmdAck;

class LargeMotor:public QObject
{
    Q_OBJECT
public:
    int MotorLeft;
    int MotorRight;
    int MotorUp1;
    int MotorUp2;
    int MotorLeftAll;
    int MotorRightAll;
    int MotorUp1All;
    int MotorUp2All;
    LargeMotor();
    bool m1Left(QString hostName, quint16 port);
    bool m1Right(QString hostName, quint16 port);
    bool m2Left(QString hostName, quint16 port);
    bool m2Right(QString hostName, quint16 port);
    bool m3Left(QString hostName, quint16 port);
    bool m3Right(QString hostName, quint16 port);
    bool m4Left(QString hostName, quint16 port);
    bool m4Right(QString hostName, quint16 port);
    bool mnStop(QString hostName, quint16 port);
    bool mnReset1(QString hostName, quint16 port);
    bool mnReset2(QString hostName, quint16 port);
    bool mnReset3(QString hostName, quint16 port);
    bool mnReset4(QString hostName, quint16 port);
    bool mnResetAll(QString hostName, quint16 port);
    bool mnGoto(qint32 a,qint32 b,qint32 c,qint32 d,QString hostName, quint16 port);
signals:
    void changeMotorState(QString label,qint32 a,qint32 b,qint32 c,qint32 d);

private:
    QTcpSocket tcpsocket;
    QString hostName;
    quint16 port;
    MotorCmd cmd;
    MotorCmdAck cmdAck;
    qint64 cmdAckLen;
    QDateTime timeout;
    bool isConnected;
    bool open(QString hostName, quint16 port);
    void prepareData();
    bool sendData();
    bool __connect();

private slots:
    void connectedHandle();
    void readHandle();
    void errorHandle(QAbstractSocket::SocketError);
    void disconnectHandle();
};

#endif // LARGEMOTOR_H
