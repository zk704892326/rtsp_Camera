#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <iostream>
#include <QPainter>
#include <QAbstractItemView>
#include <QMessageBox>
#include <QThread>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QPainter>
#include <QTime>
#include "zmqclient.h"
#include "robot_active_thread.h"

#define USING_THE_NEW_PAGE1    0x01
using namespace std;

QVector<double> skey(1),sfbvalue(1);
quint16 xs_fb_value = 0;
quint32 fb_value_counter = 0;

#define SENSOR_PLOT_DATA_INTERVAL   3 //每1s画一个随机数点在图上
#define SENSOR_PLOT_COUNTER         (3600/SENSOR_PLOT_DATA_INTERVAL) //分贝值在图表中显示的点个数，按照1s更新频率1个点
#define SENSOR_PLOT_TIMER_INTERVAL  (SENSOR_PLOT_DATA_INTERVAL * 1000) //曲线更新定时器时间
#define SENSOR_PLOT_MIN_PRESSURE    0 //分贝值在图表中显示的最小值
#define SENSOR_PLOT_MAX_PRESSURE    125 //分贝值在图表中显示最大值

#define FB_VALUE_THREADHOLD_VALUE      220
#define FB_VALUE_THREADHOMD_MAX_VALUE  300

#define RANDOM_MIN_VALUE    20      //分贝随机值最小值
#define RANDOM_MID_VALUE    60      //分贝随机值中间值
#define RANDOM_MAX_VALUE    60     //分贝随机值最大值


double now = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0 - (SENSOR_PLOT_COUNTER * SENSOR_PLOT_DATA_INTERVAL);//系统开机时间转化为秒数

QString loginnamecmd = "-u";
QString loginname = "test";
QString loginpasscmd = "-p";
QString loginpass = "test";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->CameraX = 0;
    this->CameraY = 0;
    tempWidth = 480;
    tempHeight = 360;
    video1Max = false;
    video2Max = false;

    nvideo1Max = false;
    nvideo2Max = false;
    nvideo3Max = false;
    nvideo4Max = false;

    ylplottimer = new QTimer(this);
    connect(ylplottimer,SIGNAL(timeout()),this,SLOT(ylplot_timerUpdate()));

    ui->setupUi(this);

    //获取屏幕分辨率
    quint32 screen_Width = 1280;
    quint32 screen_Height= 750;

    printf(" width  %d  height  %d\n",screen_Width,screen_Height);

    //设置窗口大小
    this->resize(screen_Width,screen_Height);
    ui->stackedWidget->setGeometry(QRect(0, 34, screen_Width,screen_Height-20));

    ui->topdownlabel->resize(screen_Width,10);
    ui->topuplabel->resize(screen_Width,12);
    ui->toplabel->resize(screen_Width-ui->topwidget->width(),32);
    ui->tableTask->resize(screen_Width-100,screen_Height-150);
    ui->tableReport->resize(screen_Width-100,screen_Height-150);
    ui->stackedWidget_2->move(959,0);
    ui->stackedWidget_2->resize(screen_Width-959,720);
    ui->gridLayoutWidget_2->resize(960,720);

    qsrand(time(NULL));

    initCustomPlotInfo();
    initPaintMap();

    ui->pointBtn->hide();

    connect(ui->settingsBtn, SIGNAL(pressed()), this, SLOT(onSettingsBtnClick()));
    connect(ui->screenshotLeftBtn, SIGNAL(pressed()), this, SLOT(onScreenshotLeftBtnClick()));
    connect(ui->screenshotRightBtn, SIGNAL(pressed()), this, SLOT(onScreenshotRightBtnClick()));

    connect(ui->motorUpBtn, SIGNAL(pressed()), this, SLOT(onMotorUpBtnClick()));
    connect(ui->motorDownBtn, SIGNAL(pressed()), this, SLOT(onMotorDownBtnClick()));
    connect(ui->motorLeftBtn, SIGNAL(pressed()), this, SLOT(onMotorLeftBtnClick()));
    connect(ui->motorRightBtn, SIGNAL(pressed()), this, SLOT(onMotorRightBtnClick()));

    connect(videos, SIGNAL(GetImage(QImage, int)), this, SLOT(SetImage(QImage, int)));
    connect(videos+1, SIGNAL(GetImage(QImage, int)), this, SLOT(SetImage(QImage, int)));

    connect(ui->m1LeftBtn, SIGNAL(clicked(bool)), this, SLOT(onM1LeftBtnClick()));
    connect(ui->m1RightBtn, SIGNAL(clicked(bool)), this, SLOT(onM1RightBtnClick()));
    connect(ui->m2LeftBtn, SIGNAL(clicked(bool)), this, SLOT(onM2LeftBtnClick()));
    connect(ui->m2RightBtn, SIGNAL(clicked(bool)), this, SLOT(onM2RightBtnClick()));
    connect(ui->m3LeftBtn, SIGNAL(clicked(bool)), this, SLOT(onM3LeftBtnClick()));
    connect(ui->m3RightBtn, SIGNAL(clicked(bool)), this, SLOT(onM3RightBtnClick()));
    connect(ui->m4LeftBtn, SIGNAL(clicked(bool)), this, SLOT(onM4LeftBtnClick()));
    connect(ui->m4RightBtn, SIGNAL(clicked(bool)), this, SLOT(onM4RightBtnClick()));
    connect(ui->mnStopBtn, SIGNAL(clicked(bool)), this, SLOT(onMnStopBtnClick()));
    connect(ui->mnResetBtn, SIGNAL(clicked(bool)), this, SLOT(onMnResetBtnClick()));

    connect(ui->switchBtn, SIGNAL(clicked(bool)), this, SLOT(onSwitchBtnClick()));

    connect(ui->homeBtn, SIGNAL(clicked(bool)), this, SLOT(onHomeBtnClick()));
    connect(ui->settingBtn, SIGNAL(clicked(bool)), this, SLOT(onSettingBtnClick()));
    connect(ui->taskBtn, SIGNAL(clicked(bool)), this, SLOT(onTaskBtnClick()));
    connect(ui->pointBtn, SIGNAL(clicked(bool)), this, SLOT(onPointBtnClick()));
    connect(ui->reportBtn, SIGNAL(clicked(bool)), this, SLOT(onReportBtnClick()));
    connect(ui->taskAddBtn, SIGNAL(clicked(bool)), this, SLOT(onTaskAddBtnClick()));
    connect(ui->taskEditBtn, SIGNAL(clicked(bool)), this, SLOT(onTaskEditBtnClick()));
    connect(ui->taskDelBtn, SIGNAL(clicked(bool)), this, SLOT(onTaskDelBtnClick()));
    connect(ui->addPointBtn, SIGNAL(clicked(bool)), this, SLOT(onPointAddBtnClick()));
    connect(ui->pointAddBtn, SIGNAL(clicked(bool)), this, SLOT(onPointAddBtnClick()));
    connect(ui->pointEditBtn, SIGNAL(clicked(bool)), this, SLOT(onPointEditBtnClick()));
    connect(ui->pointDelBtn, SIGNAL(clicked(bool)), this, SLOT(onPointDelBtnClick()));
    connect(ui->loadConfigBtn, SIGNAL(clicked(bool)), this, SLOT(onLoadConfigBtn()));

    connect(&largeMotor, SIGNAL(changeMotorState(QString,qint32,qint32,qint32,qint32)), this, SLOT(onChangeLargeMotorState(QString,qint32,qint32,qint32,qint32)));

    connect(ui->login_passwd, SIGNAL(returnPressed()), this, SLOT(onLoginAction()));
    connect(ui->login_btn, SIGNAL(clicked(bool)), this, SLOT(onLoginAction()));

    connect(ui->nmotor1up, SIGNAL(pressed()), this, SLOT(onNewMotor1UpClick()));
    connect(ui->nmotor1down, SIGNAL(pressed()), this, SLOT(onNewMotor1DownClick()));
    connect(ui->nmotor1left, SIGNAL(pressed()), this, SLOT(onNewMotor1LeftClick()));
    connect(ui->nmotor1right, SIGNAL(pressed()), this, SLOT(onNewMotor1RightClick()));
    connect(ui->nmotor1stop, SIGNAL(pressed()), this, SLOT(onNewMotor1StopClick()));

    connect(ui->nmotor2up, SIGNAL(pressed()), this, SLOT(onNewMotor2UpClick()));
    connect(ui->nmotor2down, SIGNAL(pressed()), this, SLOT(onNewMotor2DownClick()));
    connect(ui->nmotor2left, SIGNAL(pressed()), this, SLOT(onNewMotor2LeftClick()));
    connect(ui->nmotor2right, SIGNAL(pressed()), this, SLOT(onNewMotor2RightClick()));
    connect(ui->nmotor2stop, SIGNAL(pressed()), this, SLOT(onNewMotor2StopClick()));

    connect(ui->nmotor3up, SIGNAL(pressed()), this, SLOT(onNewMotor3UpClick()));
    connect(ui->nmotor3down, SIGNAL(pressed()), this, SLOT(onNewMotor3DownClick()));
    connect(ui->nmotor3stop, SIGNAL(pressed()), this, SLOT(onNewMotor3StopClick()));

    connect(ui->nmotorlist, &QTreeWidget::itemActivated,this, &MainWindow::onNewMotorListDoubleClickProcess);
    connect(ui->switchcontrol, SIGNAL(pressed()), this, SLOT(onNewMotorListSwitchProcess()));
    connect(ui->addpoint, SIGNAL(pressed()), this, SLOT(onNewMotorListAddPointProcess()));

    connect(ui->nmotor1cstop, SIGNAL(pressed()), this, SLOT(onNewMotor1CuriseStopClick()));
    connect(ui->nmotor1bup, SIGNAL(pressed()), this, SLOT(onNewMotor1BackCarUpClick()));
    connect(ui->nmotor1bstop, SIGNAL(pressed()), this, SLOT(onNewMotor1BackCarStopClick()));
    connect(ui->nmotor1bdown, SIGNAL(pressed()), this, SLOT(onNewMotor1BackCarDownClick()));
    connect(ui->nmotor4up, SIGNAL(pressed()), this, SLOT(onNewMotor4UpClick()));
    connect(ui->nmotor4down, SIGNAL(pressed()), this, SLOT(onNewMotor4DownClick()));
    connect(ui->nmotor4left, SIGNAL(pressed()), this, SLOT(onNewMotor4LeftClick()));
    connect(ui->nmotor4right, SIGNAL(pressed()), this, SLOT(onNewMotor4RightClick()));
    connect(ui->nmotor4stop, SIGNAL(pressed()), this, SLOT(onNewMotor4StopClick()));
    connect(ui->nmotor5left, SIGNAL(pressed()), this, SLOT(onNewMotor5LeftClick()));
    connect(ui->nmotor5right, SIGNAL(pressed()), this, SLOT(onNewMotor5RightClick()));
    connect(ui->nmotor5stop, SIGNAL(pressed()), this, SLOT(onNewMotor5StopClick()));

    connect(ui->startcruiseBtn, SIGNAL(pressed()), this, SLOT(onStartCruiseBtnClick()));
    connect(ui->endcruiseBtn, SIGNAL(pressed()), this, SLOT(onStopCruiseBtnClick()));
    connect(ui->pausecruiseBtn, SIGNAL(pressed()), this, SLOT(onPauseCruiseBtnClick()));
    connect(ui->genreportBtn, SIGNAL(pressed()), this, SLOT(onGenReportBtnClick()));

    ui->video1->installEventFilter(this);
    ui->video2->installEventFilter(this);

    ui->nvideo1->installEventFilter(this);
    ui->nvideo2->installEventFilter(this);
//    ui->nvideo3->installEventFilter(this);
    customPlot->installEventFilter(this);
//    ui->nvideo4->installEventFilter(this);
    paintMap->installEventFilter(this);

//    ui->homeBtn->setVisible(false);
//    ui->settingBtn->setVisible(false);
//    ui->taskBtn->setVisible(false);
//    ui->pointBtn->setVisible(false);
//    ui->reportBtn->setVisible(false);

    ui->topuplabel->setVisible(false);
    ui->topdownlabel->setVisible(false);
    ui->toplabel->setVisible(false);
    ui->topwidget->setVisible(false);

    connect(ui->taskSaveBtn, SIGNAL(clicked(bool)), this, SLOT(onTaskSaveBtn()));
    connect(ui->pointSaveBtn, SIGNAL(clicked(bool)), this, SLOT(onPointSaveBtn()));

    ui->tableTask->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablePoint->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableReport->setSelectionBehavior(QAbstractItemView::SelectRows);

    db = QSqlDatabase::addDatabase("QSQLITE");
    loadSettings();

    cmdLineLogin();

    panel = new DrawPanel(this->ui->pointedit);
    panel->setGeometry(ui->pointImage->geometry());

    connect(panel, SIGNAL(GetRect(QRect)), this, SLOT(SetPointImageArea(QRect)));

    pathpanel = new MotorPath(this->ui->motorpath);
    pathpanel->setGeometry(ui->labelpath->geometry());
    ui->labelpath->setText("");
    cruisetask.label = ui->video1;
    cruisetask.loadConfig(&settings);
    ui->checkBoxCruise->setChecked(settings.cruise);

    ui->videoUrl1->setText(settings.videos[0].url);
    ui->checkBoxVideo1->setChecked(settings.videos[0].enable);
    ui->videoUrl2->setText(settings.videos[1].url);
    ui->checkBoxVideo2->setChecked(settings.videos[1].enable);

    ui->motorIp->setText(settings.motors[0].ip);
    ui->motorPort->setText(QString::number(settings.motors[0].port, 10));
    ui->largeMotorIp->setText(settings.motors[1].ip);
    ui->largeMotorPort->setText(QString::number(settings.motors[1].port, 10));

    onSaveBtnClick();

    this->RATactive.start();
    this->RATactive.zmqClientOne.CameraX = this->CameraX;
    this->RATactive.zmqClientOne.CameraY = this->CameraY;
    this->RATactive.CameraRun = 1;
    ui->checkBox->setChecked(true);

    //this->RATactive.currentPointx = 32;
    //this->RATactive.currentPointy = 62;

    //ui->timeEdit->setTime(QTime::fromString("09:11"));


    this->socket=0;
    this->server=new QTcpServer(this);
    this->server->listen(QHostAddress::Any,8080);
    QObject::connect(this->server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

void MainWindow::newConnection(){
    this->socket=this->server->nextPendingConnection();
    //QMessageBox::about(this,"提示","有新的连接！");
    connect(this->socket,SIGNAL(readyRead()),this,SLOT(ReceiveData()));

}
void MainWindow::ReceiveData(){
   QByteArray arr=this->socket->readAll();

   QString str = arr;

//   this->RATactive.CameraRun = 1;
//   printf("%s M X  3\n",__FUNCTION__);

//   sendData_t abc;

//   abc.a1 = 1;
//   abc.a2 = 16;
//   abc.a3 = 100;
//   abc.a5 = 0;
//   abc.a4 = 0;
//   abc.a6 = 0;
//   abc.a7 = 0;
//   abc.a8 = 0;
//   abc.a9 = this->CameraX;
//   abc.a10 = this->CameraY;

//   this->RATactive.zmqClientTwo.sendText((char *)(&abc),16);
//   this->RATactive.zmqClientTwo.CarStation = 1;

   //QMessageBox::about(this,"提示","Car is Active !!!!");

   //qDebug() << str;

   qint64 num = arr.length();

   this->socket->write(arr.data(),num);

//   int i = 0;
//   for(i=0;i<arr.length();i++){
//       printf("%2X ", arr.at(i));
//   }
//   printf("\n");

   //QDataStream dst(arr);
   //QString str1;
   //QString str2;
   //dst>>str1>>str2;
   //qDebug()<<str1+str2;
   //this->ui->browser->setText(str1+str2);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        if (obj == ui->video1){
            if (video1Max){
                tempWidth=480;
                tempHeight=360;
                ui->video2->setVisible(true);
                ui->image1->setVisible(true);
                ui->image2->setVisible(true);
            } else {
                tempWidth=960;
                tempHeight=720;
                ui->video2->setVisible(false);
                ui->image1->setVisible(false);
                ui->image2->setVisible(false);
            }
            video1Max=!video1Max;
        }else if (obj==ui->video2){
            if (video2Max){
                tempWidth=480;
                tempHeight=360;
                ui->video1->setVisible(true);
                ui->image1->setVisible(true);
                ui->image2->setVisible(true);
            }else{
                tempWidth=960;
                tempHeight=720;
                ui->video1->setVisible(false);
                ui->image1->setVisible(false);
                ui->image2->setVisible(false);
            }
            video2Max=!video2Max;
        }else if (obj == ui->nvideo1){
            if (nvideo1Max){
                tempWidth=480;
                tempHeight=360;
                ui->nvideo2->setVisible(true);
//                ui->nvideo3->setVisible(true);
                customPlot->setVisible(true);
//                ui->nvideo4->setVisible(true);
                paintMap->setVisible(true);
            } else {
                tempWidth=960;
                tempHeight=720;
                ui->nvideo2->setVisible(false);
//                ui->nvideo3->setVisible(false);
                customPlot->setVisible(false);
//                ui->nvideo4->setVisible(false);
                paintMap->setVisible(false);
            }
            nvideo1Max=!nvideo1Max;
        }else if (obj == ui->nvideo2){
            if (nvideo2Max){
                tempWidth=480;
                tempHeight=360;
                ui->nvideo1->setVisible(true);
//                ui->nvideo3->setVisible(true);
                customPlot->setVisible(true);
//                ui->nvideo4->setVisible(true);
                paintMap->setVisible(true);
            } else {
                tempWidth=960;
                tempHeight=720;
                ui->nvideo1->setVisible(false);
//                ui->nvideo3->setVisible(false);
                customPlot->setVisible(false);
//                ui->nvideo4->setVisible(false);
                paintMap->setVisible(false);
            }
            nvideo2Max=!nvideo2Max;
        }
        else if (obj == customPlot){
            if (nvideo3Max){
                tempWidth=480;
                tempHeight=360;
                ui->nvideo1->setVisible(true);
                ui->nvideo2->setVisible(true);
//                ui->nvideo4->setVisible(true);
                paintMap->setVisible(true);
            } else {
                tempWidth=960;
                tempHeight=720;
                ui->nvideo1->setVisible(false);
                ui->nvideo2->setVisible(false);
//                ui->nvideo4->setVisible(false);
                paintMap->setVisible(false);
            }
            nvideo3Max=!nvideo3Max;
        }
        else if (obj == paintMap){
            if (nvideo4Max){
                tempWidth=480;
                tempHeight=360;
                ui->nvideo1->setVisible(true);
                ui->nvideo2->setVisible(true);
//                ui->nvideo3->setVisible(true);
                customPlot->setVisible(true);
            } else {
                tempWidth=960;
                tempHeight=720;
                ui->nvideo1->setVisible(false);
                ui->nvideo2->setVisible(false);
//                ui->nvideo3->setVisible(false);
                customPlot->setVisible(false);
            }
            nvideo4Max=!nvideo4Max;
        }
    }
    return QObject::eventFilter(obj, event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{

}

void MainWindow::onSaveBtnClick() {

    printf("%s\n",__FUNCTION__);

    if(ui->checkBoxVideo1->isChecked()) {
        videos[0].play(ui->videoUrl1->text(), 0);
    } else {
        videos[0].stop();
    }
    if(ui->checkBoxVideo2->isChecked()) {
        videos[1].play(ui->videoUrl2->text(), 1);
    } else {
       videos[1].stop();
    }
//    if(settings.cruise) {
//        cruisetask.play();
//    } else {
//        cruisetask.stop();
//    }

    char ConStr[128] = {0};
    char*  ch;
    QByteArray ba ;
    QString abc;

    //tcp://10.120.17.132:7766

    if(settings.cruise){

        abc = "tcp://"+this->settings.motors[0].ip+":"+QString::number(this->settings.motors[0].port, 10);

        memset(ConStr,'\0',128);

        ba = abc.toLatin1();

        ch=ba.data();

        if(this->RATactive.zmqClientOne.ConnectServer(ch,0) == 1){
            this->RATactive.zmqClientOne.start();
        }

        abc = "tcp://"+this->settings.motors[1].ip+":"+QString::number(this->settings.motors[1].port, 10);

        memset(ConStr,'\0',128);

        ba = abc.toLatin1();

        ch=ba.data();

        if(this->RATactive.zmqClientTwo.ConnectServer(ch,1) == 1){
            this->RATactive.zmqClientTwo.start();
        }
    }
}

void MainWindow::onScreenshotLeftBtnClick() {
    if (ui->video1->pixmap()!=0x0) {
        ui->image1->setPixmap(ui->video1->pixmap()->scaled(480, 360));
    }
}

void MainWindow::onScreenshotRightBtnClick() {
    if (ui->video2->pixmap()!=0x0) {
        ui->image2->setPixmap(ui->video2->pixmap()->scaled(480, 360));
    }
}

void MainWindow::SetImage(const QImage &image, const int index) {
    QPixmap pix = QPixmap::fromImage(image.scaled(tempWidth, tempHeight));
    if(0 == index) {
        ui->video1->setPixmap(pix);
        ui->nvideo1->setPixmap(pix);
    } else if(1 == index) {
        ui->video2->setPixmap(pix);
        ui->nvideo2->setPixmap(pix);
    }
}

void MainWindow::onMotorUpBtnClick() {
//    if(!motor.isOpen()) {
//        motor.open(ui->motorIp->text().toStdString().c_str(), ui->motorPort->text().toInt(), "admin", "admin");
//    }
//    if(motor.isOpen()) {
//        if(0 != motor.state) {
//            motor.stop();
//            motor.state = 0;
//            return;
//        }
//        motor.moveUp();
//        motor.state = 1;
//    }
}

void MainWindow::onMotorDownBtnClick() {
//    if(!motor.isOpen()) {
//        motor.open(ui->motorIp->text().toStdString().c_str(), ui->motorPort->text().toInt(), "admin", "admin");
//    }
//    if(motor.isOpen()) {
//        if(0 != motor.state) {
//            motor.stop();
//            motor.state = 0;
//            return;
//        }
//        motor.moveDown();
//        motor.state = 2;
//    }
}

void MainWindow::onMotorLeftBtnClick() {
//    float aa = 0,bb = 0,cc = 0;
//    int dd = 0;
//    if(!motor.isOpen()) {
//        motor.open(ui->motorIp->text().toStdString().c_str(), ui->motorPort->text().toInt(), "admin", "admin");
//    }
//    if(motor.isOpen()) {
//        if(0 != motor.state) {
//            motor.rotateGetPostion(&aa,&bb,&cc,&dd);
//            qDebug()<<aa<<"  "<<bb<<"  "<<cc<<"  "<<dd<<endl;
//            motor.stop();
//            motor.state = 0;
//            return;
//        }
//        motor.moveLeft();
//        motor.state = 3;
//    }
}

void MainWindow::onMotorRightBtnClick() {
//    if(!motor.isOpen()) {
//        motor.open(ui->motorIp->text().toStdString().c_str(), ui->motorPort->text().toInt(), "admin", "admin");
//    }
//    if(motor.isOpen()) {
//        if(0 != motor.state) {
//            motor.stop();
//            motor.state = 0;
//            return;
//        }
//        motor.moveRight();
//        motor.state = 4;
//    }
}

void MainWindow::onM1LeftBtnClick() {
    largeMotor.m1Left(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
}

void MainWindow::onM1RightBtnClick() {
    largeMotor.m1Right(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
}

void MainWindow::onM2LeftBtnClick() {
    largeMotor.m2Left(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
}

void MainWindow::onM2RightBtnClick() {
    largeMotor.m2Right(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
}

void MainWindow::onM3LeftBtnClick() {
    largeMotor.m3Left(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
}

void MainWindow::onM3RightBtnClick() {
    largeMotor.m3Right(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
}

void MainWindow::onM4LeftBtnClick() {
    largeMotor.m4Left(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
}

void MainWindow::onM4RightBtnClick() {
    largeMotor.m4Right(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
}

void MainWindow::onMnStopBtnClick() {
    largeMotor.mnStop(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
}

void MainWindow::onMnResetBtnClick() {

    if(ui->lineEditGuo->text() == "1"){
       largeMotor.mnReset1(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
    }
    else if(ui->lineEditGuo->text() == "2"){
       largeMotor.mnReset2(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
    }
    else if(ui->lineEditGuo->text() == "3"){
       largeMotor.mnReset3(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
    }else{
       largeMotor.mnResetAll(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
    }

    //largeMotor.mnReset2(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
    //largeMotor.mnReset3(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
    //largeMotor.mnReset4(ui->largeMotorIp->text(), ui->largeMotorPort->text().toInt());
}

void MainWindow::onSwitchBtnClick() {
    int index = ui->ctrlpanel->currentIndex() + 1;
    if(index >= ui->ctrlpanel->count()) {
        index = 0;
    }
    ui->ctrlpanel->setCurrentIndex(index);
}

void MainWindow::onSettingsBtnClick() {

    printf("[guozhixin] %s %s \n",__FUNCTION__,DB_PATH);

    db.setDatabaseName(DB_PATH);
    if(!db.open()) {
        qDebug()<<db.lastError();
    } else {
        qDebug()<<"db open success";
    }
    QSqlQuery query;
    query.prepare("UPDATE configs SET data=:data WHERE name='settings';");
    QJsonObject json;
    QJsonObject json_obj;
    json.insert("cruise", ui->checkBoxCruise->isChecked());

    json_obj.empty();
    json_obj.insert("url", ui->videoUrl1->text());
    json_obj.insert("enable", ui->checkBoxVideo1->isChecked());
    json.insert("video1", json_obj);

    json_obj.empty();
    json_obj.insert("url", ui->videoUrl2->text());
    json_obj.insert("enable", ui->checkBoxVideo2->isChecked());
    json.insert("video2", json_obj);

    json_obj.empty();
    json_obj.insert("ip", ui->motorIp->text());
    json_obj.insert("port", ui->motorPort->text().toInt());
    json.insert("motor1", json_obj);

    json_obj.empty();
    json_obj.insert("ip", ui->largeMotorIp->text());
    json_obj.insert("port", ui->largeMotorPort->text().toInt());
    json.insert("motor2", json_obj);

    query.bindValue(0, QString(QJsonDocument(json).toJson()));
    if(!query.exec()) {
        qDebug()<<db.lastError();
    }
    db.commit();
    db.close();

    settings.videos[0].url = ui->videoUrl1->text();
    settings.videos[0].enable = ui->checkBoxVideo1->isChecked();

    settings.videos[1].url = ui->videoUrl2->text();
    settings.videos[1].enable = ui->checkBoxVideo2->isChecked();

    settings.motors[0].ip = ui->motorIp->text();
    settings.motors[0].port = ui->motorPort->text().toInt();

    settings.motors[1].ip = ui->largeMotorIp->text();
    settings.motors[1].port = ui->largeMotorPort->text().toInt();
    settings.cruise = ui->checkBoxCruise->isChecked();

    //this->RATactive.CameraRun = this->ui->checkBox->isChecked();//ui->checkBoxCruise->isChecked();

    onSaveBtnClick();
}

void MainWindow::onChangeLargeMotorState(QString label,qint32 a,qint32 b,qint32 c,qint32 d) {
   // ui->largeMotorState->setText(label);

    qDebug()<<QString::number(a, 10)<<","<<QString::number(b, 10)<<","<<QString::number(c, 10)<<","<<QString::number(d, 10);

    //ui->lineEdit_4->setText(QString::number(a, 10));
    //ui->lineEdit_3->setText(QString::number(b, 10));
    //ui->lineEdit_2->setText(QString::number(c, 10));
    //ui->lineEdit->setText(QString::number(d, 10));

}

bool MainWindow::loadSettings() {
    db.setDatabaseName(DB_PATH);
    if(!db.open()) {
        qDebug()<<db.lastError();
    } else {
//        qDebug()<<"db open success";
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM configs WHERE name='settings';");
    if(!query.exec()) {
        qDebug()<<db.lastError();
    }
    QJsonDocument json;
    QJsonObject json_obj;
    QJsonParseError json_err;
    for( int r=0; query.next(); r++ ) {
        json = QJsonDocument::fromJson(query.value(1).toByteArray(), &json_err);
        json_obj = json.object();
        json_obj = json_obj.value("video1").toObject();
        settings.videos[0].url = json_obj.value("url").toString();
        settings.videos[0].enable = json_obj.value("enable").toBool();

        json_obj = json.object();
        json_obj = json_obj.value("video2").toObject();
        settings.videos[1].url = json_obj.value("url").toString();
        settings.videos[1].enable = json_obj.value("enable").toBool();

        json_obj = json.object();
        json_obj = json_obj.value("motor1").toObject();
        settings.motors[0].ip = json_obj.value("ip").toString();
        settings.motors[0].port = json_obj.value("port").toInt();

        json_obj = json.object();
        json_obj = json_obj.value("motor2").toObject();
        settings.motors[1].ip = json_obj.value("ip").toString();
        settings.motors[1].port = json_obj.value("port").toInt();

        json_obj = json.object();
        settings.cruise = json_obj.value("cruise").toBool();
        break;
    }
    db.close();
    return true;
}

void MainWindow::updatemotorlist(QString motorinfo)
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, motorinfo);

    ui->nmotorlist->addTopLevelItem(item);
    if (!ui->nmotorlist->currentItem()) {
        ui->nmotorlist->setCurrentItem(ui->nmotorlist->topLevelItem(0));
        ui->nmotorlist->setEnabled(true);
    }
}

void MainWindow::initCustomPlotInfo()
{
    customPlot = new QCustomPlot(this);
    customPlot->resize(480, 360);
    //是否显示图例，设置为false则不显示
    customPlot->legend->setVisible(false);
    customPlot->legend->setFont(QFont("Microsoft YaHei",6));
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignCenter|Qt::AlignRight);
//    customPlot->axisRect()->setRangeZoomFactor(1,3);
    //可变数组存放绘图的坐标的数据
    skey[0] = now;
    sfbvalue[0] = 0;

    //向绘图区域QCustomPlot添加曲线
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::red,2));
    customPlot->graph(0)->setName(tr("分贝值"));
    customPlot->graph(0)->setData(skey, sfbvalue);
    //设置坐标轴名称
    customPlot->xAxis->setLabel(" ");
//    customPlot->xAxis->setLabel("时间/s");
//    customPlot->yAxis->setLabel("分贝/db");
    //设置坐标轴显示范围，否则只能看到默认范围
//    customPlot->xAxis->setRange(-11, 11);
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setTicker(dateTicker);
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    //当前的显示从开机哪一点开始
    customPlot->xAxis->setRange(now, (now+SENSOR_PLOT_COUNTER * SENSOR_PLOT_DATA_INTERVAL));
    customPlot->yAxis->setRange(SENSOR_PLOT_MIN_PRESSURE, SENSOR_PLOT_MAX_PRESSURE);
    //右上角的坐标轴
//    customPlot->xAxis2->setVisible(true);
//    customPlot->yAxis2->setVisible(true);
    //显示图名
//    customPlot->plotLayout()->insertRow(0);
//    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, tr("分贝值曲线图")));
    //初始化曲线数据
    initCustomPlotData();
    //启动定时器，开始曲线的刷新
    ylplottimer->start(SENSOR_PLOT_TIMER_INTERVAL);
    ui->gridLayout_2->addWidget(customPlot, 1, 0, 1, 1);
}

void MainWindow::initCustomPlotData()
{
    quint32 i = 0;
    double nowtime = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    nowtime -= SENSOR_PLOT_COUNTER * SENSOR_PLOT_DATA_INTERVAL;
    quint16 nxs_fb_value = xs_fb_value;
    quint32 j = 0;

    for(i = 0; i< SENSOR_PLOT_COUNTER; i++){
        skey.append(nowtime);
        //测试曲线图绘制的调试代码
        j = i % FB_VALUE_THREADHOMD_MAX_VALUE;
        if(j <FB_VALUE_THREADHOLD_VALUE){
            nxs_fb_value = genRandomDate(RANDOM_MIN_VALUE,RANDOM_MID_VALUE);
        }else{
            nxs_fb_value = genRandomDate(RANDOM_MIN_VALUE,RANDOM_MAX_VALUE);
        }
        sfbvalue.append(nxs_fb_value);

        customPlot->graph(0)->addData(nowtime,nxs_fb_value);
        customPlot->replot();
        nowtime += SENSOR_PLOT_DATA_INTERVAL;
    }
}

quint16 MainWindow::genRandomDate(quint16 minvalue, quint16 maxvalue)
{
    quint16 nrdata = minvalue + qrand() % (maxvalue - minvalue);
    return nrdata;
}

void MainWindow::initPaintMap()
{
    paintMap = new PaintLabel(this);
    paintMap->resize(480, 360);

    paintMap->setStyleSheet(QStringLiteral("border-image: url(:/sy_04.png);"));
    ui->gridLayout_2->addWidget(paintMap, 1, 1, 1, 1);
}

void MainWindow::cmdLineLogin()
{
    if(("admin" == loginname) && ("admin" == loginpass)) {
        ui->topuplabel->setVisible(true);
        ui->topdownlabel->setVisible(true);
        ui->toplabel->setVisible(true);
        ui->topwidget->setVisible(true);
#if USING_THE_NEW_PAGE1 == 1
        ui->stackedWidget->setCurrentIndex(8);
#else
        ui->stackedWidget->setCurrentIndex(1);
#endif
        ui->stackedWidget_2->setCurrentIndex(0);
    }else if(("user" == loginname) && ("user" == loginpass)) {
        ui->topuplabel->setVisible(true);
        ui->topdownlabel->setVisible(true);
        ui->toplabel->setVisible(true);
        ui->topwidget->setVisible(true);

#if USING_THE_NEW_PAGE1 == 1
        ui->stackedWidget->setCurrentIndex(8);
#else
        ui->stackedWidget->setCurrentIndex(1);
#endif
        ui->stackedWidget_2->setCurrentIndex(1);
    }else{
        onLogoutAction();
    }
}

void MainWindow::onLoginAction() {
    if("admin" == ui->login_name->text() && "admin" == ui->login_passwd->text()) {
//        ui->homeBtn->setVisible(true);
//        ui->settingBtn->setVisible(true);
//        ui->taskBtn->setVisible(true);
//        ui->pointBtn->setVisible(true);
//        ui->reportBtn->setVisible(true);

        ui->topuplabel->setVisible(true);
        ui->topdownlabel->setVisible(true);
        ui->toplabel->setVisible(true);
        ui->topwidget->setVisible(true);
#if USING_THE_NEW_PAGE1 == 1
        ui->stackedWidget->setCurrentIndex(8);
#else
        ui->stackedWidget->setCurrentIndex(1);
#endif
        ui->stackedWidget_2->setCurrentIndex(0);
    }else if("user" == ui->login_name->text() && "user" == ui->login_passwd->text()) {
        ui->topuplabel->setVisible(true);
        ui->topdownlabel->setVisible(true);
        ui->toplabel->setVisible(true);
        ui->topwidget->setVisible(true);

#if USING_THE_NEW_PAGE1 == 1
        ui->stackedWidget->setCurrentIndex(8);
#else
        ui->stackedWidget->setCurrentIndex(1);
#endif
        ui->stackedWidget_2->setCurrentIndex(1);
    }
}

void MainWindow::onHomeBtnClick() {
#if USING_THE_NEW_PAGE1 == 1
    ui->stackedWidget->setCurrentIndex(8);
#else
    ui->stackedWidget->setCurrentIndex(1);
#endif
}

void MainWindow::onSettingBtnClick() {
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::onTaskBtnClick() {
    db.setDatabaseName(DB_PATH);
    if(!db.open()) {
        qDebug()<<db.lastError();
    } else {
//        qDebug()<<"db open success";
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(QString("SELECT id, time, enable FROM tasks ORDER BY time ASC;"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("time"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("enable"));
    ui->tableTask->setModel(model);
    ui->tableTask->setColumnHidden(0, true);
    //db.close();
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::onPointBtnClick() {
    db.setDatabaseName(DB_PATH);
    if(!db.open()) {
        qDebug()<<db.lastError();
    } else {
//        qDebug()<<"db open success";
    }

    QSqlQueryModel *modelpoint = new QSqlQueryModel();
    modelpoint->setQuery(QString("SELECT name, motor, img_path, img_area, key_point FROM points ORDER BY name ASC;"));
    modelpoint->setHeaderData(0,Qt::Horizontal,QObject::tr("name"));
    modelpoint->setHeaderData(1,Qt::Horizontal,QObject::tr("motor"));
    modelpoint->setHeaderData(2,Qt::Horizontal,QObject::tr("img_path"));
    modelpoint->setHeaderData(3,Qt::Horizontal,QObject::tr("img_area"));
    modelpoint->setHeaderData(4,Qt::Horizontal,QObject::tr("key_point"));
    ui->tablePoint->setModel(modelpoint);
    ui->tablePoint->setColumnWidth(1, 300);
    //db.close();
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::onReportBtnClick() {
    db.setDatabaseName(DB_PATH);
    if(!db.open()) {
        qDebug()<<db.lastError();
    } else {
//        qDebug()<<"db open success";
    }

    QSqlQueryModel *modelreport = new QSqlQueryModel();
    modelreport->setQuery(QString("SELECT time,point,video,audio,tempera,state FROM records ORDER BY time ASC;"));
    modelreport->setHeaderData(0,Qt::Horizontal,QObject::tr("time"));
    modelreport->setHeaderData(1,Qt::Horizontal,QObject::tr("point"));
    modelreport->setHeaderData(2,Qt::Horizontal,QObject::tr("video"));
    modelreport->setHeaderData(3,Qt::Horizontal,QObject::tr("audio"));
    modelreport->setHeaderData(4,Qt::Horizontal,QObject::tr("tempera"));
    modelreport->setHeaderData(5,Qt::Horizontal,QObject::tr("state"));
    ui->tableReport->setModel(modelreport);
    ui->tableReport->setColumnWidth(0, 300);
    //db.close();
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::onTaskAddBtnClick() {
//    ui->taskName->setEnabled(true);
    ui->taskName->setText("");
    ui->taskName->setVisible(false);
    //ui->taskTime->setText("");
    ui->taskTime->setTime(QTime::fromString("08:00"));
    ui->taskEnable->setChecked(true);
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::onPointAddBtnClick() {
    if(1 == ui->stackedWidget->currentIndex()) {
        onLoadConfigBtn();
    }
    ui->pointNum->setEnabled(true);
    ui->pointNum->setValue(0);

    float aa = 0,bb = 0,cc = 0;
    int dd = 0;

//    if(!motor.isOpen()) {
//        motor.open(ui->motorIp->text().toStdString().c_str(), ui->motorPort->text().toInt(), "admin", "admin");
//    }
//    motor.rotateGetPostion(&aa,&bb,&cc,&dd);

    QString motorPoint = QString("%1,%2,%3,%4")//,%5,%6,%7,%8")
            .arg(this->largeMotor.MotorLeft)
            .arg(this->largeMotor.MotorRight)
            .arg(this->largeMotor.MotorUp1)
            .arg(this->largeMotor.MotorUp2);
//            .arg(this->motor.motorX)
//            .arg(this->motor.motorY)
//            .arg(this->motor.motorZoom)
//            .arg(this->motor.motorDirection);
    ui->pointMotor->setText(motorPoint);
    qDebug()<<motorPoint;
    //ui->pointImage->setText("");
    ui->pointImageArea->setText("");
    ui->keyPoint->setChecked(false);
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::onLogoutAction() {
    ui->stackedWidget->setCurrentIndex(0);
//    ui->homeBtn->setVisible(false);
//    ui->settingBtn->setVisible(false);
//    ui->taskBtn->setVisible(false);
//    ui->reportBtn->setVisible(false);
    ui->topuplabel->setVisible(false);
    ui->topdownlabel->setVisible(false);
    ui->toplabel->setVisible(false);
    ui->topwidget->setVisible(false);
}

void MainWindow::onTaskEditBtnClick() {
    QModelIndexList selected = ui->tableTask->selectionModel()->selectedIndexes();
    if(selected.count()>0) {
        QString name = selected.at(0).data().toString();
        QString time = selected.at(1).data().toString();
        QString enable = selected.at(2).data().toString();
//        ui->taskName->setEnabled(false);
        ui->taskName->setVisible(false);
        ui->taskName->setText(name);
        ui->taskTime->setTime(QTime::fromString(time));
        ui->taskEnable->setChecked("true" == enable?true:false);
        ui->stackedWidget->setCurrentIndex(6);
    }
}

void MainWindow::onTaskDelBtnClick() {
    QModelIndexList selected = ui->tableTask->selectionModel()->selectedIndexes();
    if(selected.count()>0) {
        QString name = selected.at(0).data().toString();
        db.setDatabaseName(DB_PATH);
        if(!db.open()) {
            qDebug()<<db.lastError();
        } else {
//            qDebug()<<"db open success";
        }
        QSqlQuery query;
        query.prepare("DELETE FROM tasks WHERE id=:id;");
        query.bindValue(0, name);
        if(!query.exec()) {
            qDebug()<<"DELETE ERROR"<<db.lastError();
        }
        db.commit();
        db.close();
        onTaskBtnClick();
    }
}

void MainWindow::onPointEditBtnClick() {
    QModelIndexList selected = ui->tablePoint->selectionModel()->selectedIndexes();
    if(selected.count()>0) {
        QString name = selected.at(0).data().toString();
        QString motor = selected.at(1).data().toString();
        //QString img_path = selected.at(2).data().toString();
        QString img_area = selected.at(3).data().toString();
        QString key_point = selected.at(4).data().toString();
        ui->pointNum->setEnabled(false);
        ui->pointNum->setValue(name.toInt());
        ui->pointMotor->setText(motor);
        QPixmap pix;
        pix.load(QString(IMG_DIR) + "/" + name + ".png");
        ui->pointImage->setPixmap(pix);
        ui->pointImageArea->setText(img_area);
        int x=0, y=0, w=0, h=0;
        sscanf(img_area.toStdString().c_str(), "%d,%d,%d,%d", &x, &y, &w, &h);
        this->panel->setRect(QRect(x, y, w, h));
        //qDebug()<<x<<y<<w<<h;
        ui->keyPoint->setChecked("true" == key_point?true:false);
        ui->stackedWidget->setCurrentIndex(7);
    }
}

void MainWindow::onPointDelBtnClick() {
    QModelIndexList selected = ui->tablePoint->selectionModel()->selectedIndexes();
    if(selected.count()>0) {
        QString name = selected.at(0).data().toString();
        db.setDatabaseName(DB_PATH);
        if(!db.open()) {
            qDebug()<<db.lastError();
        } else {
//            qDebug()<<"db open success";
        }
        QSqlQuery query;
        query.prepare("DELETE FROM points WHERE name=:name;");
        query.bindValue(0, name);
        if(!query.exec()) {
            qDebug()<<"DELETE ERROR"<<db.lastError();
        }
        db.commit();
        db.close();
        onPointBtnClick();
    }
}

void MainWindow::onLoadConfigBtn() {
    if (ui->video1->pixmap()!=0x0) {
        ui->pointImage->setPixmap(ui->video1->pixmap()->scaled(480, 360));
    }
}

void MainWindow::onTaskSaveBtn() {

    printf("%s\n",__FUNCTION__);

    db.setDatabaseName(DB_PATH);
    if(!db.open()) {
        qDebug()<<db.lastError();
    } else {
//        qDebug()<<"db open success";
    }
    bool Ok = true;
    QSqlQuery query;
    QString taskEnable = ui->taskEnable->isChecked()?"true":"false";
    if("" == ui->taskName->text()) {
        query.prepare("INSERT INTO tasks (time, enable) VALUES (:time, :enable);");
        query.bindValue(0, ui->taskTime->text());
        query.bindValue(1, taskEnable);
        if(!query.exec()) {
            qDebug()<<"INSERT ERROR"<<db.lastError();
            QMessageBox::information(0, "Task", "Add Error!         ", QMessageBox::Close);
            Ok = false;
        }
    } else {
        query.prepare("UPDATE tasks SET time=:time, enable=:enable WHERE id=:id;");
        query.bindValue(0, ui->taskTime->text());
        query.bindValue(1, taskEnable);
        query.bindValue(2, ui->taskName->text());
        if(!query.exec()) {
            qDebug()<<"UPDATE ERROR"<<db.lastError();
            QMessageBox::information(0, "Task", "Edit Error!        ", QMessageBox::Close);
            Ok = false;
        }
    }
    db.commit();
    db.close();
    if(Ok) {
        onTaskBtnClick();
        onSaveBtnClick();
    }
}

void MainWindow::onPointSaveBtn() {

    printf("%s\n",__FUNCTION__);

    db.setDatabaseName(DB_PATH);
    if(!db.open()) {
        qDebug()<<db.lastError();
    } else {
//        qDebug()<<"db open success";
    }
    bool Ok = true;
    QSqlQuery query;
    QString keyPoint = ui->keyPoint->isChecked()?"true":"false";
    if(ui->pointNum->isEnabled()) {
        query.prepare("INSERT INTO points (name, motor, img_path, img_area, key_point) VALUES (:name, :motor, :img_path, :img_area, :enable);");
        query.bindValue(0, QString::number(ui->pointNum->value()));
        query.bindValue(1, ui->pointMotor->text());
        query.bindValue(2, QString::number(ui->pointNum->value()) + ".png");
        query.bindValue(3, ui->pointImageArea->text());
        if(ui->pointImage->pixmap()) {
            ui->pointImage->pixmap()->save(QString(IMG_DIR) + "/" + QString::number(ui->pointNum->value()) + ".png");
        }
        query.bindValue(4, keyPoint);
        if(!query.exec()) {
            qDebug()<<"INSERT ERROR"<<db.lastError();
            QMessageBox::information(0, "Point", "Add Error!         ", QMessageBox::Close);
            Ok = false;
        }
    } else {
        query.prepare("UPDATE points SET motor=:motor, img_path=:img_path, img_area=:img_area, key_point=:key_point WHERE name=:name;");
        query.bindValue(0, ui->pointMotor->text());
        query.bindValue(1, QString::number(ui->pointNum->value()) + ".png");
        query.bindValue(2, ui->pointImageArea->text());
        query.bindValue(3, keyPoint);
        query.bindValue(4, QString::number(ui->pointNum->value()));
        if(!query.exec()) {
            qDebug()<<"UPDATE ERROR"<<db.lastError();
            QMessageBox::information(0, "Point", "Edit Error!        ", QMessageBox::Close);
            Ok = false;
        }
    }
    db.commit();
    db.close();
    if(Ok) {
        onPointBtnClick();
        onSaveBtnClick();
    }
}

void MainWindow::SetPointImageArea(const QRect &rect) {
    QString rectstr = QString("%1,%2,%3,%4").arg(rect.left()).arg(rect.top()).arg(rect.width()).arg(rect.height());
    ui->pointImageArea->setText(rectstr);
    //    qDebug()<<rect;
}

void MainWindow::onNewMotor1UpClick()
{
    printf("%s M X  3\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 100;
    abc.a5 = 0;
    abc.a4 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientTwo.sendText((char *)(&abc),16);
    this->RATactive.zmqClientTwo.CarStation = 0;
}

void MainWindow::onNewMotor1DownClick()
{
    printf("%s M -X  3\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = -100;
    abc.a5 = 0;
    abc.a4 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientTwo.sendText((char *)(&abc),16);
    this->RATactive.zmqClientTwo.CarStation = 0;
}

void MainWindow::onNewMotor1StopClick()  //MCar Stop
{
    printf("%s M S  \n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    //this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientTwo.sendText((char *)(&abc),16);
    this->RATactive.zmqClientTwo.CarStation = 0;
}

//MCar Go up

void MainWindow::onNewMotor1BackCarUpClick()
{
    printf("%s M Z\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a5 = 10;
    abc.a4 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientTwo.sendText((char *)(&abc),16);
    this->RATactive.zmqClientTwo.CarStation = 0;
}

void MainWindow::onNewMotor1BackCarDownClick()
{
    printf("%s M -Z\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a5 = -10;
    abc.a4 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientTwo.sendText((char *)(&abc),16);
    this->RATactive.zmqClientTwo.CarStation = 0;
}

void MainWindow::onNewMotor1BackCarStopClick()  //M Car Stop
{
    printf("%s M S\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a5 = 0;
    abc.a4 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientTwo.sendText((char *)(&abc),16);
    this->RATactive.zmqClientTwo.CarStation = 0;
}

//MCar Tupan Up Down

void MainWindow::onNewMotor1LeftClick()
{
    printf("%s Z X\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 100;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = 0;
    abc.a10 = 0;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor1RightClick()
{
    printf("%s Z -X  3\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = -100;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = 0;
    abc.a10 = 0;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor1CuriseStopClick() // ZCar go Stop
{
    printf("%s Z S\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a5 = 0;
    abc.a4 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = 0;
    abc.a10 = 0;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor2UpClick()
{
    printf("%s Z D\n",__FUNCTION__);

    sendData_t abc;
    int tmp = 0;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    tmp = this->CameraX + 5;
    if(tmp > 0){
       this->CameraX = this->CameraX + 5;
    }

    this->RATactive.zmqClientOne.CameraX = this->CameraX;
    this->RATactive.zmqClientOne.CameraY = this->CameraY;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    printf("Camera X   %d \n",this->CameraX);

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor2DownClick()
{
    printf("%s Z -D\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    this->CameraX = this->CameraX - 5;
    this->RATactive.zmqClientOne.CameraX = this->CameraX;
    this->RATactive.zmqClientOne.CameraY = this->CameraY;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    printf("Camera X   %d \n",this->CameraX);

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor2LeftClick()
{
    printf("%s Z E\n",__FUNCTION__);

    sendData_t abc;
    int tmp = 0;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a8 = 0;
    abc.a7 = 0;
    tmp = this->CameraY - 5;
    if(tmp > 0){
      this->CameraY = this->CameraY - 5;
    }
    this->RATactive.zmqClientOne.CameraX = this->CameraX;
    this->RATactive.zmqClientOne.CameraY = this->CameraY;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    printf("Camera Y   %d \n",this->CameraY);

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor2RightClick()
{
    printf("%s Z -E\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a8 = 0;
    abc.a7 = 0;
    this->CameraY = this->CameraY + 5;
    this->RATactive.zmqClientOne.CameraX = this->CameraX;
    this->RATactive.zmqClientOne.CameraY = this->CameraY;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    printf("Camera Y   %d \n",this->CameraY);

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor2StopClick()
{
    printf("%s Z S\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;

    abc.a9 = 0;
    abc.a10 = 0;
    //abc.a9 = this->CameraX;
    //abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor3UpClick()
{
    printf("%s Z C\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 1;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor3DownClick()
{
    printf("%s Z -C\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a5 = 0;
    abc.a8 = -1;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor3StopClick()
{
    printf("%s Z S\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a8 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor4UpClick()
{
    printf("%s Z A\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 500;
    abc.a9 = 0;
    abc.a7 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor4DownClick()
{
    printf("%s Z -A\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = -500;
    abc.a9 = 0;
    abc.a7 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor4LeftClick()
{
    printf("%s Z B\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a8 = 0;
    abc.a7 = 50;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor4RightClick()
{
    printf("%s Z -B\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a8 = 0;
    abc.a7 = -50;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor4StopClick()
{
    printf("%s Z S\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a5 = 0;
    abc.a6 = 0;
    abc.a8 = 0;
    abc.a7 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor5LeftClick()
{
    printf("%s Z Z\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a5 = 1;
    abc.a8 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor5RightClick()
{
    printf("%s Z -Z\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a5 = -1;
    abc.a8 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotor5StopClick()
{
    printf("%s Z S\n",__FUNCTION__);

    sendData_t abc;

    abc.a1 = 1;
    abc.a2 = 16;
    abc.a3 = 0;
    abc.a4 = 0;
    abc.a6 = 0;
    abc.a7 = 0;
    abc.a5 = 0;
    abc.a8 = 0;
    abc.a9 = this->CameraX;
    abc.a10 = this->CameraY;

    this->RATactive.zmqClientOne.sendText((char *)(&abc),16);
    this->RATactive.zmqClientOne.CarStation = 0;
}

void MainWindow::onNewMotorListDoubleClickProcess(QTreeWidgetItem *item, int)
{
    //onNewMotorListSwitchProcess();
}

void MainWindow::onNewMotorListSwitchProcess()
{
    if(ui->nmotorlist->currentItem() == NULL){
          return;
    }

    QString motorinfo = ui->nmotorlist->currentItem()->text(0);
}

void MainWindow::onNewMotorListAddPointProcess()
{

}


void MainWindow::ylplot_timerUpdate()
{
    quint32 vsize = skey.size();
    quint32 temp = 0;
    double nowtime = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    quint16 nxs_fb_value = xs_fb_value;

     //测试曲线图绘制的调试代码
     temp = fb_value_counter % FB_VALUE_THREADHOMD_MAX_VALUE;
     if(temp <FB_VALUE_THREADHOLD_VALUE){
         nxs_fb_value = genRandomDate(RANDOM_MIN_VALUE,RANDOM_MID_VALUE);
     }else{
         nxs_fb_value = genRandomDate(RANDOM_MIN_VALUE,RANDOM_MAX_VALUE);
     }
     fb_value_counter++;

     if(fb_value_counter == FB_VALUE_THREADHOMD_MAX_VALUE){
         fb_value_counter = 0;
     }

    //当前的点数量还不足以绘制一屏幕，则不需要移动数据，直接append即可
    if(vsize < SENSOR_PLOT_COUNTER){
        skey.append(nowtime);
        sfbvalue.append(nxs_fb_value);

        customPlot->graph(0)->addData(nowtime,nxs_fb_value);
        customPlot->replot();
    }else{
        //先移除第一个元素
         skey.remove(0);
         sfbvalue.remove(0);
        //增加新数据
         skey.append(nowtime);
         sfbvalue.append(nxs_fb_value);

         customPlot->graph(0)->setData(skey,sfbvalue);
         now+=SENSOR_PLOT_DATA_INTERVAL;
         customPlot->xAxis->setRange(now, (now+SENSOR_PLOT_COUNTER * SENSOR_PLOT_DATA_INTERVAL));
         customPlot->replot();
    }

    paintMap->updatePointInfo(this->RATactive.currentPointx,this->RATactive.currentPointy);

    //printf(" X   %d   Y   %d   \n",this->RATactive.currentPointx,this->RATactive.currentPointy);
}

void MainWindow::onStartCruiseBtnClick()
{
    this->RATactive.CameraRun = 1;
//    printf("%s M X  3\n",__FUNCTION__);

//    sendData_t abc;

//    abc.a1 = 1;
//    abc.a2 = 16;
//    abc.a3 = 100;
//    abc.a5 = 0;
//    abc.a4 = 0;
//    abc.a6 = 0;
//    abc.a7 = 0;
//    abc.a8 = 0;
//    abc.a9 = this->CameraX;
//    abc.a10 = this->CameraY;

//    this->RATactive.zmqClientTwo.sendText((char *)(&abc),16);
    if(this->RATactive.zmqClientOne.Xx1 == 1){
        this->onNewMotor1LeftClick();
        this->RATactive.zmqClientTwo.CarStation = 1;
        this->RATactive.isStatas2 = 1;
        this->RATactive.zmqClientOne.CarStation = 1;
    }else{
        this->onNewMotor1UpClick();
        this->RATactive.zmqClientTwo.CarStation = 1;
    }
//    this->RATactive.zmqClientTwo.disconnect();
//    this->RATactive.zmqClientOne.disconnect();
}

void MainWindow::onStopCruiseBtnClick()
{
    this->RATactive.CameraRun = 0;
}

void MainWindow::onPauseCruiseBtnClick()
{
    this->RATactive.CameraRun = 0;
}

void MainWindow::onGenReportBtnClick()
{

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked){
        this->RATactive.CameraRun = 1;
    }else{
        this->RATactive.CameraRun = 0;
    }
}

