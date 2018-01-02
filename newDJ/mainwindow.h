#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <posix_qextserialport.h>
#include <QTimer>
#include <QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_local_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_socket_clicked();

    void on_pushButton_set_clicked();

    QHostAddress getLocalHostIP();

    void on_goto1_clicked();

    void on_goto2_clicked();

    void on_getValue1_clicked();

    void on_getValue2_clicked();

public slots:
    void slot_read_my_com();

    void SendMess(int count1,int count2,int count3,int count4,int comcount,int com1,int com2,int com3,int com4,int speed);

    void slotConnectClient();

    void slotReadTcpData0();

    void slotDisconnected0();

    void slotReadTcpData1();

    void slotDisconnected1();

    void slotReadTcpData2();

    void slotDisconnected2();

    void slotReadTcpData3();

    void slotDisconnected3();

    void slotReadTcpData4();

    void slotDisconnected4();

    void slotReadTcpData5();

    void slotDisconnected5();

    void slotReadTcpData6();

    void slotDisconnected6();

    void slotReadTcpData7();

    void slotDisconnected7();

    void update_mess();

private:
    int num;
    int comnum;

    int zhouLen1;
    int zhouLen2;
    int zhouLen3;
    int zhouLen4;

    int gotonum11;
    int gotonum12;
    int gotonum13;
    int gotonum14;

    int gotonum21;
    int gotonum22;
    int gotonum23;
    int gotonum24;

    Ui::MainWindow *ui;

    Posix_QextSerialPort *gp_my_com; // 串口的选择和串口的初始化

    QTimer *gp_receive_data_timer; // 定时进行数据接收

    QTimer *timer;

    int port;

    QTcpServer *m_pTcpServer;   //server tcp socket
    QTcpSocket *m_pConnectSocket0;      //client connect socket
    QTcpSocket *m_pConnectSocket1;      //client connect socket
    QTcpSocket *m_pConnectSocket2;      //client connect socket
    QTcpSocket *m_pConnectSocket3;      //client connect socket
    QTcpSocket *m_pConnectSocket4;      //client connect socket
    QTcpSocket *m_pConnectSocket5;      //client connect socket
    QTcpSocket *m_pConnectSocket6;      //client connect socket
    QTcpSocket *m_pConnectSocket7;      //client connect socket
};

#endif // MAINWINDOW_H
