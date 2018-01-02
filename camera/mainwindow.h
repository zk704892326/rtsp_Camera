#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
//#include "motor/motor.h"
#include "largemotor.h"
#include "ffmpeg.h"
#include "drawpanel.h"
#include "motorpath.h"
#include "cruisetask.h"
#include "common.h"
#include <QTreeWidgetItem>
#include "zmqclient.h"
#include "robot_active_thread.h"
#include "qcustomplot.h"
#include "paintlabel.h"
#include<QTcpServer>
#include<QTcpSocket>

extern QString loginnamecmd;
extern QString loginname;
extern QString loginpasscmd;
extern QString loginpass;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    int tempWidth;
    int tempHeight;
    bool video1Max;
    bool video2Max;
    bool nvideo1Max;
    bool nvideo2Max;
    bool nvideo3Max;
    bool nvideo4Max;

    int CameraX,CameraY;

    Robot_Active_Thread RATactive;
    bool eventFilter(QObject *obj, QEvent *event);
    CruiseTask cruisetask;
    //Motor motor;
    LargeMotor largeMotor;
    FFmpeg videos[2];
    DrawPanel *panel;
    MotorPath *pathpanel;
    Settings_t settings;
    QSqlDatabase db;
    bool loadSettings();
    void updatemotorlist(QString motorinfo);
    //分贝曲线图
    QCustomPlot *customPlot;
    QTimer *ylplottimer;
    void initCustomPlotInfo();
    void initCustomPlotData();
    quint16 genRandomDate(quint16 minvalue, quint16 maxvalue);
    //画点处理
    PaintLabel *paintMap;

    QTcpServer * server;
    QTcpSocket * socket;

    void initPaintMap();

    //命令行登录
    void cmdLineLogin();

public slots:
    void onChangeLargeMotorState(QString label,qint32 a,qint32 b,qint32 c,qint32 d);

    void newConnection();
    void ReceiveData();
private slots:
    void SetImage(const QImage &image, const int index);
    void onSaveBtnClick();
    void onScreenshotLeftBtnClick();
    void onScreenshotRightBtnClick();

    void onMotorUpBtnClick();
    void onMotorDownBtnClick();
    void onMotorLeftBtnClick();
    void onMotorRightBtnClick();

    void onM1LeftBtnClick();
    void onM1RightBtnClick();
    void onM2LeftBtnClick();
    void onM2RightBtnClick();
    void onM3LeftBtnClick();
    void onM3RightBtnClick();
    void onM4LeftBtnClick();
    void onM4RightBtnClick();
    void onMnStopBtnClick();
    void onMnResetBtnClick();

    void onSwitchBtnClick();

    void onSettingsBtnClick();

    void onLoginAction();
    void onHomeBtnClick();
    void onSettingBtnClick();
    void onTaskBtnClick();
    void onPointBtnClick();
    void onReportBtnClick();
    void onTaskAddBtnClick();
    void onPointAddBtnClick();
    void onLogoutAction();

    void onTaskEditBtnClick();
    void onTaskDelBtnClick();
    void onPointEditBtnClick();
    void onPointDelBtnClick();
    void onLoadConfigBtn();

    void onTaskSaveBtn();
    void onPointSaveBtn();

    void SetPointImageArea(const QRect &rect);

    void onNewMotor1UpClick();
    void onNewMotor1DownClick();
    void onNewMotor1LeftClick();
    void onNewMotor1RightClick();
    void onNewMotor1StopClick();

    void onNewMotor2UpClick();
    void onNewMotor2DownClick();
    void onNewMotor2LeftClick();
    void onNewMotor2RightClick();
    void onNewMotor2StopClick();

    void onNewMotor3UpClick();
    void onNewMotor3DownClick();
    void onNewMotor3StopClick();

    void onNewMotor1CuriseStopClick();
    void onNewMotor1BackCarUpClick();
    void onNewMotor1BackCarStopClick();
    void onNewMotor1BackCarDownClick();
    void onNewMotor4UpClick();
    void onNewMotor4DownClick();
    void onNewMotor4LeftClick();
    void onNewMotor4RightClick();
    void onNewMotor4StopClick();
    void onNewMotor5LeftClick();
    void onNewMotor5RightClick();
    void onNewMotor5StopClick();


    void onNewMotorListDoubleClickProcess(QTreeWidgetItem *item, int);
    void onNewMotorListSwitchProcess();
    void onNewMotorListAddPointProcess();

    void ylplot_timerUpdate();
    void onStartCruiseBtnClick();
    void onStopCruiseBtnClick();
    void onPauseCruiseBtnClick();
    void onGenReportBtnClick();
    void on_checkBox_clicked(bool checked);
};

#endif // MAINWINDOW_H
