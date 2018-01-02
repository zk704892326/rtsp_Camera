#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QTcpServer>
#include <QMessageBox>

int bytesToInt(QByteArray bytes) {
    int addr = bytes[0] & 0x000000FF;
    addr |= ((bytes[1] << 8) & 0x0000FF00);
    addr |= ((bytes[2] << 16) & 0x00FF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
}

QByteArray  intToByte(int number)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = (uchar)  (0x000000ff & number);
    abyte0[1] = (uchar) ((0x0000ff00 & number) >> 8);
    abyte0[2] = (uchar) ((0x00ff0000 & number) >> 16);
    abyte0[3] = (uchar) ((0xff000000 & number) >> 24);
    return abyte0;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFont font("ZYSong18030",12);
    setFont(font);

    this->num = 1;

    ui->setupUi(this);
    ui->lineEdit_L1->setText("");
    ui->lineEdit_L2->setText("");
    ui->lineEdit_L3->setText("");
    ui->lineEdit_L4->setText("");

    this->zhouLen1 = 0;
    this->zhouLen2 = 0;
    this->zhouLen3 = 0;
    this->zhouLen4 = 0;

    ui->label_Z1->setText("");
    ui->label_Z2->setText("");
    ui->label_Z3->setText("");
    ui->label_Z4->setText("");


    this->m_pConnectSocket0 = NULL;
    this->m_pConnectSocket1 = NULL;
    this->m_pConnectSocket2 = NULL;
    this->m_pConnectSocket3 = NULL;

     gp_receive_data_timer = new QTimer;

     gp_my_com = NULL;

     timer = new QTimer(this);
     connect(timer, SIGNAL(timeout()),this, SLOT(update_mess()));
     timer->start(10000);

     comnum = 0;
}

MainWindow::~MainWindow()
{
    delete ui;

    delete gp_receive_data_timer;
}

void MainWindow::on_pushButton_open_clicked()
{
    QString lv_port_name_str = ui->lineEdit->text(); //获取串口名
    lv_port_name_str = QString("/dev/").append(lv_port_name_str);

    gp_my_com = new Posix_QextSerialPort(lv_port_name_str, QextSerialBase::Polling); // 串口的选择和串口的初始化
    gp_my_com->open(QIODevice::ReadWrite); // 用ReadWrite可读写的方式进行打开串口
    gp_my_com->setBaudRate(BAUD115200);
    gp_my_com->setDataBits(DATA_8);
    gp_my_com->setParity(PAR_NONE);
    gp_my_com->setStopBits(STOP_1);
    gp_my_com->setTimeout(100);

    gp_my_com->setFlowControl(FLOW_OFF); //数据流控制，使用无数据流控制的默认设置

    gp_receive_data_timer->start(50);
    connect(gp_receive_data_timer, SIGNAL(timeout()), this, SLOT(slot_read_my_com()));
}

void MainWindow::update_mess()
{
    comnum++;
    qDebug("guozhixin %d\n",comnum);
}

void MainWindow::slot_read_my_com()
{
    QByteArray lv_temp_byte = NULL;

    lv_temp_byte = gp_my_com->readAll(); // 读取数据
    QByteArray data;
    int len1 = 0,len2 = 0,len3 = 0,len4 = 0;
    data.resize(4);

    //qDebug("get Message  %d \n",lv_temp_byte.length());

    if((lv_temp_byte != NULL)&&(lv_temp_byte.length() == 27)){

        if(m_pConnectSocket0 != NULL){
            m_pConnectSocket0->write(lv_temp_byte);
        }
        if(m_pConnectSocket1 != NULL){
            m_pConnectSocket1->write(lv_temp_byte);
        }
        if(m_pConnectSocket2 != NULL){
            m_pConnectSocket2->write(lv_temp_byte);
        }
        if(m_pConnectSocket3 != NULL){
            m_pConnectSocket3->write(lv_temp_byte);
        }

        if((lv_temp_byte[9] == 2)||(lv_temp_byte[9] == 3)){
            data[0] = lv_temp_byte[5];
            data[1] = lv_temp_byte[6];
            data[2] = lv_temp_byte[7];
            data[3] = lv_temp_byte[8];

            len1 = bytesToInt(data);

            ui->lineEdit_L1->setText(QString::number(len1));
        }

        if(lv_temp_byte[9] == 4){
            data[0] = lv_temp_byte[5];
            data[1] = lv_temp_byte[6];
            data[2] = lv_temp_byte[7];
            data[3] = lv_temp_byte[8];

            this->zhouLen1 = bytesToInt(data);
            ui->label_Z1->setText(QString::number(this->zhouLen1));
        }

        if((lv_temp_byte[14] == 2)||(lv_temp_byte[14] == 3)){
            data[0] = lv_temp_byte[10];
            data[1] = lv_temp_byte[11];
            data[2] = lv_temp_byte[12];
            data[3] = lv_temp_byte[13];

            len2 = bytesToInt(data);
            ui->lineEdit_L2->setText(QString::number(len2));
        }

        if(lv_temp_byte[14] == 4){
            data[0] = lv_temp_byte[10];
            data[1] = lv_temp_byte[11];
            data[2] = lv_temp_byte[12];
            data[3] = lv_temp_byte[13];

            this->zhouLen2 = bytesToInt(data);
            ui->label_Z2->setText(QString::number(this->zhouLen2));
        }

        if((lv_temp_byte[19] == 2)||(lv_temp_byte[19] == 3)){
            data[0] = lv_temp_byte[15];
            data[1] = lv_temp_byte[16];
            data[2] = lv_temp_byte[17];
            data[3] = lv_temp_byte[18];

            len3 = bytesToInt(data);
            ui->lineEdit_L3->setText(QString::number(len3));
        }

        if(lv_temp_byte[19] == 4){
            data[0] = lv_temp_byte[15];
            data[1] = lv_temp_byte[16];
            data[2] = lv_temp_byte[17];
            data[3] = lv_temp_byte[18];

            this->zhouLen3 = bytesToInt(data);
            ui->label_Z3->setText(QString::number(this->zhouLen3));
        }

        if((lv_temp_byte[24] == 2)||(lv_temp_byte[24] == 3)){
            data[0] = lv_temp_byte[20];
            data[1] = lv_temp_byte[21];
            data[2] = lv_temp_byte[22];
            data[3] = lv_temp_byte[23];

            len4 = bytesToInt(data);
            ui->lineEdit_L4->setText(QString::number(len4));
        }

        if(lv_temp_byte[24] == 4){
            data[0] = lv_temp_byte[20];
            data[1] = lv_temp_byte[21];
            data[2] = lv_temp_byte[22];
            data[3] = lv_temp_byte[23];

            this->zhouLen4 = bytesToInt(data);
            ui->label_Z4->setText(QString::number(this->zhouLen4));
        }


        if((lv_temp_byte[24] == 3)&&(lv_temp_byte[19] == 3)&&(lv_temp_byte[14] == 3)&&(lv_temp_byte[9] == 3)){

              //if((len1 == this->gotonum11)&&(len2 == this->gotonum12)&&(len3 == this->gotonum13)&&(len4 == this->gotonum14)){
              //    SendMess(this->gotonum21,this->gotonum22,this->gotonum23,this->gotonum24,3,1,1,1,1,ui->spinBox_speed->text().toInt());
              //}

              //if((len1 == this->gotonum21)&&(len2 == this->gotonum22)&&(len3 == this->gotonum23)&&(len4 == this->gotonum24)){
              //    SendMess(this->gotonum11,this->gotonum12,this->gotonum13,this->gotonum14,3,1,1,1,1,ui->spinBox_speed->text().toInt());
              //}

        }
        qDebug("len1   %d  ,len2  %d  ,len3  %d\n",len1,len2,len3,len4);

        QString lv_receive_str = QString::fromUtf8(lv_temp_byte.toHex());

        qDebug()<< lv_temp_byte ;

        //ui->textEdit->insertPlainText(lv_receive_str); // 无处理显示
    }
}

void MainWindow::on_pushButton_close_clicked()
{
    gp_my_com->close();
}
/*

command
1:Move
2:stop
3:goto
4:reset
5:set long num

*/
void MainWindow::SendMess(int count1,int count2,int count3,int count4,int comcount
                          ,int com1,int com2,int com3,int com4
                          ,int speed)
{
    int i = 0;
    QByteArray s; // 获取消息
    QByteArray step;
    s.resize(32);
    step.resize(4);
    s[0] = 'E';
    s[1] = 'M';
    s[2] = 'M';
    s[3] = 'A';
    s[4] = this->num;

    if(step.size() == 4){
        step = intToByte(count1);
        s[5] = step[0];
        s[6] = step[1];
        s[7] = step[2];
        s[8] = step[3];

        step = intToByte(count2);
        s[11] = step[0];
        s[12] = step[1];
        s[13] = step[2];
        s[14] = step[3];

        step = intToByte(count3);
        s[17] = step[0];
        s[18] = step[1];
        s[19] = step[2];
        s[20] = step[3];

        step = intToByte(count4);
        s[23] = step[0];
        s[24] = step[1];
        s[25] = step[2];
        s[26] = step[3];
    }

    s[9] = 0; s[15] = 0;s[21] = 0; s[27] = 0;

    /*if(ui->spinBox->text().toInt() == 1){
      s[9] = 1;
    }else if(ui->spinBox->text().toInt() == 2){
        s[15] = 1;
    }else if(ui->spinBox->text().toInt() == 3){
        s[21] = 1;
    }*/

    if(com1 == 1){
        s[9] = comcount;
    }
    if(com2 == 1){
        s[15] = comcount;
    }
    if(com3 == 1){
        s[21] = comcount;
    }
    if(com4 == 1){
        s[27] = comcount;
    }

    s[10] = speed;
    s[16] = speed;
    s[22] = speed;
    s[28] = speed;

    s[29] = 0;
    s[30] = 0;
    for (i = 4; i < 30; i++) {
        s[30] = s[30] + s[i];
    }
    this->num++;
    if(this->num == 256)this->num = 1;

    if(gp_my_com != NULL)
        gp_my_com->write(s); // 无处理发送
}

void MainWindow::on_pushButton_up_clicked()
{
    int a = 0,b = 0,c = 0,d = 0;
    int a1 = 0,b1 = 0,c1 = 0,d1 = 0;

    if(ui->spinBox->text().toInt() == 1){
      a = 1;
      a1 = 10000000000;
    }else if(ui->spinBox->text().toInt() == 2){
      b = 1;
      b1 = 10000000000;
    }else if(ui->spinBox->text().toInt() == 3){
      c = 1;
      c1 = 10000000000;
    }else if(ui->spinBox->text().toInt() == 4){
      d = 1;
      d1 = 10000000000;
    }


    SendMess(a1,b1,c1,d1,1,a,b,c,d,ui->spinBox_speed->text().toInt());
}

void MainWindow::on_pushButton_down_clicked()
{
    int a = 0,b = 0,c = 0,d = 0;
    int a1 = 0,b1 = 0,c1 = 0,d1 = 0;

    if(ui->spinBox->text().toInt() == 1){
      a = 1;
      a1 = -10000000000;
    }else if(ui->spinBox->text().toInt() == 2){
      b = 1;
      b1 = -10000000000;
    }else if(ui->spinBox->text().toInt() == 3){
      c = 1;
      c1 = -10000000000;
    }else if(ui->spinBox->text().toInt() == 4){
      d = 1;
      d1 = -10000000000;
    }


    SendMess(a1,b1,c1,d1,1,a,b,c,d,ui->spinBox_speed->text().toInt());
}

void MainWindow::on_pushButton_stop_clicked()
{
    SendMess(0,0,0,0,2,1,1,1,1,ui->spinBox_speed->text().toInt());
}

void MainWindow::on_pushButton_local_clicked()
{
    int line1 = ui->lineEdit_L1->text().toInt();
    int line2 = ui->lineEdit_L2->text().toInt();
    int line3 = ui->lineEdit_L3->text().toInt();
    int line4 = ui->lineEdit_L4->text().toInt();

    int a = 1,b = 1,c = 1,d = 1;

    SendMess(line1,line2,line3,line4,3,a,b,c,d,ui->spinBox_speed->text().toInt());

}

void MainWindow::on_pushButton_reset_clicked()
{

    SendMess(0,0,0,0,4,1,1,1,1,ui->spinBox_speed->text().toInt());

}

QHostAddress MainWindow::getLocalHostIP()
{
  QList<QHostAddress> AddressList = QNetworkInterface::allAddresses();
  QHostAddress result;
  foreach(QHostAddress address, AddressList){
      if(address.protocol() == QAbstractSocket::IPv4Protocol &&
         address != QHostAddress::Null &&
         address != QHostAddress::LocalHost){
          if (address.toString().contains("127.0.")){
            continue;
          }
          result = address;
          break;
      }
  }
  return result;
}

void MainWindow::on_pushButton_socket_clicked()
{
    int port = ui->lineEdit_Port->text().toInt();

    m_pTcpServer = new QTcpServer(this);
    if (!m_pTcpServer->listen(QHostAddress::Any, port))
    {
    //listen fail
    qDebug()<<m_pTcpServer->errorString();
    QMessageBox::information(this, tr("Listen Fail"), m_pTcpServer->errorString());
    }

    connect(m_pTcpServer, SIGNAL(newConnection()), this, SLOT(slotConnectClient()));

    QMessageBox::information(this, tr("IP Address"), getLocalHostIP().toString());

    m_pConnectSocket0 = NULL;
    m_pConnectSocket1 = NULL;
    m_pConnectSocket2 = NULL;
    m_pConnectSocket3 = NULL;

    ui->pushButton_socket->setEnabled(false);
}

void MainWindow::slotReadTcpData0()
{
    QByteArray byteArray;

    byteArray = m_pConnectSocket0->readAll();

    qDebug() <<byteArray.length(); //byteArray.toHex().toStdString().c_str();

    if(gp_my_com != NULL)
        gp_my_com->write(byteArray); // 无处理发送

    //处理数据
    //processPakcet(byteArray);
}

void MainWindow::slotDisconnected0()
{
    m_pConnectSocket0->close();
    m_pConnectSocket0 = NULL;
}

void MainWindow::slotReadTcpData1()
{
    QByteArray byteArray;

    byteArray = m_pConnectSocket1->readAll();

    qDebug() << byteArray.length();//toHex().toStdString().c_str();

    if(gp_my_com != NULL)
        gp_my_com->write(byteArray); // 无处理发送

    //处理数据
    //processPakcet(byteArray);
}

void MainWindow::slotDisconnected1()
{
    m_pConnectSocket1->close();
    m_pConnectSocket1 = NULL;
}

void MainWindow::slotReadTcpData2()
{
    QByteArray byteArray;

    byteArray = m_pConnectSocket2->readAll();

    qDebug() << byteArray.length();//toHex().toStdString().c_str();

    if(gp_my_com != NULL)
        gp_my_com->write(byteArray); // 无处理发送

    //处理数据
    //processPakcet(byteArray);
}

void MainWindow::slotDisconnected2()
{
    m_pConnectSocket2->close();
    m_pConnectSocket2 = NULL;
}

void MainWindow::slotReadTcpData3()
{
    QByteArray byteArray;

    byteArray = m_pConnectSocket3->readAll();

    qDebug() << byteArray.length();//toHex().toStdString().c_str();

    if(gp_my_com != NULL)
        gp_my_com->write(byteArray); // 无处理发送

    //处理数据
    //processPakcet(byteArray);
}

void MainWindow::slotDisconnected4()
{
    m_pConnectSocket4->close();
    m_pConnectSocket4 = NULL;
}

void MainWindow::slotReadTcpData4()
{
    QByteArray byteArray;

    byteArray = m_pConnectSocket4->readAll();

    qDebug() << byteArray.length();//toHex().toStdString().c_str();

    if(gp_my_com != NULL)
        gp_my_com->write(byteArray); // 无处理发送
}

void MainWindow::slotDisconnected5()
{
    m_pConnectSocket5->close();
    m_pConnectSocket5 = NULL;
}

void MainWindow::slotReadTcpData5()
{
    QByteArray byteArray;

    byteArray = m_pConnectSocket5->readAll();

    qDebug() << byteArray.length();//toHex().toStdString().c_str();

    if(gp_my_com != NULL)
        gp_my_com->write(byteArray); // 无处理发送
}

void MainWindow::slotDisconnected6()
{
    m_pConnectSocket6->close();
    m_pConnectSocket6 = NULL;
}

void MainWindow::slotReadTcpData6()
{
    QByteArray byteArray;

    byteArray = m_pConnectSocket6->readAll();

    qDebug() << byteArray.length();//toHex().toStdString().c_str();

    if(gp_my_com != NULL)
        gp_my_com->write(byteArray); // 无处理发送
}

void MainWindow::slotDisconnected7()
{
    m_pConnectSocket7->close();
    m_pConnectSocket7 = NULL;
}

void MainWindow::slotReadTcpData7()
{
    QByteArray byteArray;

    byteArray = m_pConnectSocket7->readAll();

    qDebug() << byteArray.length();//toHex().toStdString().c_str();

    if(gp_my_com != NULL)
        gp_my_com->write(byteArray); // 无处理发送
}

void MainWindow::slotDisconnected3()
{
    m_pConnectSocket3->close();
    m_pConnectSocket3 = NULL;
}

void MainWindow::slotConnectClient()
{
    if(m_pConnectSocket0 == NULL){
            m_pConnectSocket0 = m_pTcpServer->nextPendingConnection();
            connect(m_pConnectSocket0, SIGNAL(readyRead()), this, SLOT(slotReadTcpData0()));
            connect(m_pConnectSocket0, SIGNAL(disconnected()),
                        this, SLOT(slotDisconnected0()));
    }

    if(m_pConnectSocket1 == NULL){
                m_pConnectSocket1 = m_pTcpServer->nextPendingConnection();
                connect(m_pConnectSocket1, SIGNAL(readyRead()), this, SLOT(slotReadTcpData1()));
                connect(m_pConnectSocket1, SIGNAL(disconnected()),
                        this, SLOT(slotDisconnected1()));
    }
    if(m_pConnectSocket2 == NULL){
                m_pConnectSocket2 = m_pTcpServer->nextPendingConnection();
                connect(m_pConnectSocket2, SIGNAL(readyRead()), this, SLOT(slotReadTcpData2()));
                connect(m_pConnectSocket2, SIGNAL(disconnected()),
                        this, SLOT(slotDisconnected2()));
    }
    if(m_pConnectSocket3 == NULL){
                m_pConnectSocket3 = m_pTcpServer->nextPendingConnection();
                connect(m_pConnectSocket3, SIGNAL(readyRead()), this, SLOT(slotReadTcpData3()));
                connect(m_pConnectSocket3, SIGNAL(disconnected()),
                        this, SLOT(slotDisconnected3()));
    }
    if(m_pConnectSocket4 == NULL){
            m_pConnectSocket4 = m_pTcpServer->nextPendingConnection();
            connect(m_pConnectSocket4, SIGNAL(readyRead()), this, SLOT(slotReadTcpData4()));
            connect(m_pConnectSocket4, SIGNAL(disconnected()),
                        this, SLOT(slotDisconnected4()));
    }

    if(m_pConnectSocket5 == NULL){
                m_pConnectSocket5 = m_pTcpServer->nextPendingConnection();
                connect(m_pConnectSocket5, SIGNAL(readyRead()), this, SLOT(slotReadTcpData5()));
                connect(m_pConnectSocket5, SIGNAL(disconnected()),
                        this, SLOT(slotDisconnected5()));
    }
    if(m_pConnectSocket6 == NULL){
                m_pConnectSocket6 = m_pTcpServer->nextPendingConnection();
                connect(m_pConnectSocket6, SIGNAL(readyRead()), this, SLOT(slotReadTcpData6()));
                connect(m_pConnectSocket6, SIGNAL(disconnected()),
                        this, SLOT(slotDisconnected6()));
    }
    if(m_pConnectSocket7 == NULL){
                m_pConnectSocket7 = m_pTcpServer->nextPendingConnection();
                connect(m_pConnectSocket7, SIGNAL(readyRead()), this, SLOT(slotReadTcpData7()));
                connect(m_pConnectSocket7, SIGNAL(disconnected()),
                        this, SLOT(slotDisconnected7()));
    }
}

void MainWindow::on_pushButton_set_clicked()
{
    int line1 = ui->lineEdit_num->text().toInt();
    int line2 = ui->lineEdit_num->text().toInt();
    int line3 = ui->lineEdit_num->text().toInt();
    int line4 = ui->lineEdit_num->text().toInt();

    int a = 0,b = 0,c = 0,d = 0;

    if(ui->spinBox->text().toInt() == 1){
      a = 1;
    }else if(ui->spinBox->text().toInt() == 2){
      b = 1;
    }else if(ui->spinBox->text().toInt() == 3){
      c = 1;
    }else if(ui->spinBox->text().toInt() == 4){
      d = 1;
    }


    SendMess(line1,line2,line3,line4,5,a,b,c,d,ui->spinBox_speed->text().toInt());
}

void MainWindow::on_goto1_clicked()
{
    this->gotonum11 = ui->lineEdit_L1->text().toInt();
    this->gotonum12 = ui->lineEdit_L2->text().toInt();
    this->gotonum13 = ui->lineEdit_L3->text().toInt();
    this->gotonum14 = ui->lineEdit_L4->text().toInt();

}

void MainWindow::on_goto2_clicked()
{
    this->gotonum21 = ui->lineEdit_L1->text().toInt();
    this->gotonum22 = ui->lineEdit_L2->text().toInt();
    this->gotonum23 = ui->lineEdit_L3->text().toInt();
    this->gotonum24 = ui->lineEdit_L4->text().toInt();

}

void MainWindow::on_getValue1_clicked()
{

     ui->lineEdit_L1->setText(QString::number(this->gotonum11));
     ui->lineEdit_L2->setText(QString::number(this->gotonum12));
     ui->lineEdit_L3->setText(QString::number(this->gotonum13));
     ui->lineEdit_L4->setText(QString::number(this->gotonum14));
}

void MainWindow::on_getValue2_clicked()
{
    ui->lineEdit_L1->setText(QString::number(this->gotonum21));
    ui->lineEdit_L2->setText(QString::number(this->gotonum22));
    ui->lineEdit_L3->setText(QString::number(this->gotonum23));
    ui->lineEdit_L4->setText(QString::number(this->gotonum24));
}
