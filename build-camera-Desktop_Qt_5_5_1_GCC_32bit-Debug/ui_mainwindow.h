/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionHome;
    QAction *actionSetting;
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *login;
    QLineEdit *login_name;
    QLineEdit *login_passwd;
    QPushButton *login_btn;
    QLabel *login_avatar;
    QWidget *home;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *image1;
    QLabel *video1;
    QLabel *video2;
    QLabel *image2;
    QStackedWidget *ctrlpanel;
    QWidget *pagectrl;
    QLabel *screenshot;
    QPushButton *screenshotRightBtn;
    QPushButton *m2LeftBtn;
    QPushButton *screenshotLeftBtn;
    QPushButton *m4LeftBtn;
    QPushButton *m3LeftBtn;
    QPushButton *m4RightBtn;
    QPushButton *motorUpBtn;
    QPushButton *m2RightBtn;
    QPushButton *m1RightBtn;
    QPushButton *mnStopBtn;
    QLabel *motor2;
    QPushButton *motorLeftBtn;
    QPushButton *motorRightBtn;
    QLabel *motor1;
    QPushButton *m1LeftBtn;
    QPushButton *motorDownBtn;
    QPushButton *m3RightBtn;
    QPushButton *addPointBtn;
    QLabel *shortcut;
    QPushButton *mnResetBtn;
    QLineEdit *lineEditGuo;
    QWidget *motorpath;
    QLabel *labelpath;
    QPushButton *switchBtn;
    QWidget *setting;
    QLineEdit *largeMotorPort;
    QLineEdit *motorIp;
    QLineEdit *videoUrl2;
    QLineEdit *largeMotorIp;
    QLineEdit *motorPort;
    QLabel *label_motor1;
    QLabel *label_motor2;
    QLabel *label_rtsp2;
    QLineEdit *videoUrl1;
    QLabel *label_rtsp1;
    QPushButton *settingsBtn;
    QCheckBox *checkBoxVideo1;
    QCheckBox *checkBoxVideo2;
    QPushButton *cancelBtn;
    QLabel *label_motor2_2;
    QCheckBox *checkBoxCruise;
    QWidget *task;
    QTableView *tableTask;
    QPushButton *taskAddBtn;
    QPushButton *taskEditBtn;
    QPushButton *taskDelBtn;
    QWidget *point;
    QTableView *tablePoint;
    QPushButton *pointDelBtn;
    QPushButton *pointEditBtn;
    QPushButton *pointAddBtn;
    QWidget *report;
    QPushButton *report_export_2;
    QLabel *label_normal_2;
    QCheckBox *task_enable_4;
    QTableView *tableReport;
    QWidget *taskedit;
    QPushButton *taskSaveBtn;
    QLabel *label_task_name_6;
    QLineEdit *taskName;
    QLabel *label_motor2_4;
    QCheckBox *taskEnable;
    QTimeEdit *taskTime;
    QWidget *pointedit;
    QLabel *label_task_name;
    QLineEdit *pointMotor;
    QLabel *label_task_name_5;
    QLabel *pointImage;
    QLineEdit *pointImageArea;
    QLabel *label_task_name_8;
    QPushButton *pointSaveBtn;
    QCheckBox *keyPoint;
    QLabel *label_motor2_3;
    QPushButton *loadConfigBtn;
    QSpinBox *pointNum;
    QPushButton *homeBtn;
    QPushButton *settingBtn;
    QPushButton *taskBtn;
    QPushButton *reportBtn;
    QPushButton *pointBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(870, 511);
        MainWindow->setAnimated(true);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionHome = new QAction(MainWindow);
        actionHome->setObjectName(QStringLiteral("actionHome"));
        actionSetting = new QAction(MainWindow);
        actionSetting->setObjectName(QStringLiteral("actionSetting"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 30, 870, 481));
        stackedWidget->setLineWidth(0);
        login = new QWidget();
        login->setObjectName(QStringLiteral("login"));
        login_name = new QLineEdit(login);
        login_name->setObjectName(QStringLiteral("login_name"));
        login_name->setGeometry(QRect(330, 200, 211, 31));
        login_passwd = new QLineEdit(login);
        login_passwd->setObjectName(QStringLiteral("login_passwd"));
        login_passwd->setGeometry(QRect(330, 250, 211, 31));
        login_passwd->setEchoMode(QLineEdit::Password);
        login_btn = new QPushButton(login);
        login_btn->setObjectName(QStringLiteral("login_btn"));
        login_btn->setGeometry(QRect(330, 300, 211, 31));
        login_avatar = new QLabel(login);
        login_avatar->setObjectName(QStringLiteral("login_avatar"));
        login_avatar->setGeometry(QRect(410, 130, 51, 51));
        login_avatar->setPixmap(QPixmap(QString::fromUtf8(":/user.png")));
        login_avatar->setScaledContents(false);
        stackedWidget->addWidget(login);
        home = new QWidget();
        home->setObjectName(QStringLiteral("home"));
        gridLayoutWidget = new QWidget(home);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 641, 481));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        image1 = new QLabel(gridLayoutWidget);
        image1->setObjectName(QStringLiteral("image1"));
        image1->setFrameShape(QFrame::Box);
        image1->setLineWidth(0);

        gridLayout->addWidget(image1, 1, 0, 1, 1);

        video1 = new QLabel(gridLayoutWidget);
        video1->setObjectName(QStringLiteral("video1"));
        video1->setFrameShape(QFrame::Box);
        video1->setLineWidth(0);

        gridLayout->addWidget(video1, 0, 0, 1, 1);

        video2 = new QLabel(gridLayoutWidget);
        video2->setObjectName(QStringLiteral("video2"));
        video2->setFrameShape(QFrame::Box);
        video2->setLineWidth(0);

        gridLayout->addWidget(video2, 0, 1, 1, 1);

        image2 = new QLabel(gridLayoutWidget);
        image2->setObjectName(QStringLiteral("image2"));
        image2->setFrameShape(QFrame::Box);
        image2->setLineWidth(0);

        gridLayout->addWidget(image2, 1, 1, 1, 1);

        ctrlpanel = new QStackedWidget(home);
        ctrlpanel->setObjectName(QStringLiteral("ctrlpanel"));
        ctrlpanel->setGeometry(QRect(650, 0, 211, 421));
        pagectrl = new QWidget();
        pagectrl->setObjectName(QStringLiteral("pagectrl"));
        screenshot = new QLabel(pagectrl);
        screenshot->setObjectName(QStringLiteral("screenshot"));
        screenshot->setGeometry(QRect(0, 290, 91, 17));
        screenshotRightBtn = new QPushButton(pagectrl);
        screenshotRightBtn->setObjectName(QStringLiteral("screenshotRightBtn"));
        screenshotRightBtn->setGeometry(QRect(120, 310, 81, 27));
        m2LeftBtn = new QPushButton(pagectrl);
        m2LeftBtn->setObjectName(QStringLiteral("m2LeftBtn"));
        m2LeftBtn->setGeometry(QRect(10, 145, 81, 27));
        screenshotLeftBtn = new QPushButton(pagectrl);
        screenshotLeftBtn->setObjectName(QStringLiteral("screenshotLeftBtn"));
        screenshotLeftBtn->setGeometry(QRect(10, 310, 81, 27));
        m4LeftBtn = new QPushButton(pagectrl);
        m4LeftBtn->setObjectName(QStringLiteral("m4LeftBtn"));
        m4LeftBtn->setGeometry(QRect(10, 215, 81, 27));
        m3LeftBtn = new QPushButton(pagectrl);
        m3LeftBtn->setObjectName(QStringLiteral("m3LeftBtn"));
        m3LeftBtn->setGeometry(QRect(10, 180, 81, 27));
        m4RightBtn = new QPushButton(pagectrl);
        m4RightBtn->setObjectName(QStringLiteral("m4RightBtn"));
        m4RightBtn->setGeometry(QRect(120, 215, 81, 27));
        motorUpBtn = new QPushButton(pagectrl);
        motorUpBtn->setObjectName(QStringLiteral("motorUpBtn"));
        motorUpBtn->setGeometry(QRect(10, 20, 81, 27));
        m2RightBtn = new QPushButton(pagectrl);
        m2RightBtn->setObjectName(QStringLiteral("m2RightBtn"));
        m2RightBtn->setGeometry(QRect(120, 145, 81, 27));
        m1RightBtn = new QPushButton(pagectrl);
        m1RightBtn->setObjectName(QStringLiteral("m1RightBtn"));
        m1RightBtn->setGeometry(QRect(120, 110, 81, 27));
        mnStopBtn = new QPushButton(pagectrl);
        mnStopBtn->setObjectName(QStringLiteral("mnStopBtn"));
        mnStopBtn->setGeometry(QRect(10, 250, 81, 27));
        motor2 = new QLabel(pagectrl);
        motor2->setObjectName(QStringLiteral("motor2"));
        motor2->setGeometry(QRect(0, 90, 61, 17));
        motorLeftBtn = new QPushButton(pagectrl);
        motorLeftBtn->setObjectName(QStringLiteral("motorLeftBtn"));
        motorLeftBtn->setGeometry(QRect(10, 55, 81, 27));
        motorRightBtn = new QPushButton(pagectrl);
        motorRightBtn->setObjectName(QStringLiteral("motorRightBtn"));
        motorRightBtn->setGeometry(QRect(120, 55, 81, 27));
        motor1 = new QLabel(pagectrl);
        motor1->setObjectName(QStringLiteral("motor1"));
        motor1->setGeometry(QRect(0, 0, 61, 17));
        m1LeftBtn = new QPushButton(pagectrl);
        m1LeftBtn->setObjectName(QStringLiteral("m1LeftBtn"));
        m1LeftBtn->setGeometry(QRect(10, 110, 81, 27));
        m1LeftBtn->setFocusPolicy(Qt::StrongFocus);
        motorDownBtn = new QPushButton(pagectrl);
        motorDownBtn->setObjectName(QStringLiteral("motorDownBtn"));
        motorDownBtn->setGeometry(QRect(120, 20, 81, 27));
        m3RightBtn = new QPushButton(pagectrl);
        m3RightBtn->setObjectName(QStringLiteral("m3RightBtn"));
        m3RightBtn->setGeometry(QRect(120, 180, 81, 27));
        addPointBtn = new QPushButton(pagectrl);
        addPointBtn->setObjectName(QStringLiteral("addPointBtn"));
        addPointBtn->setGeometry(QRect(10, 370, 81, 27));
        shortcut = new QLabel(pagectrl);
        shortcut->setObjectName(QStringLiteral("shortcut"));
        shortcut->setGeometry(QRect(0, 350, 91, 17));
        mnResetBtn = new QPushButton(pagectrl);
        mnResetBtn->setObjectName(QStringLiteral("mnResetBtn"));
        mnResetBtn->setGeometry(QRect(120, 250, 81, 27));
        lineEditGuo = new QLineEdit(pagectrl);
        lineEditGuo->setObjectName(QStringLiteral("lineEditGuo"));
        lineEditGuo->setGeometry(QRect(130, 280, 61, 27));
        ctrlpanel->addWidget(pagectrl);
        motorpath = new QWidget();
        motorpath->setObjectName(QStringLiteral("motorpath"));
        labelpath = new QLabel(motorpath);
        labelpath->setObjectName(QStringLiteral("labelpath"));
        labelpath->setGeometry(QRect(20, 20, 165, 400));
        ctrlpanel->addWidget(motorpath);
        switchBtn = new QPushButton(home);
        switchBtn->setObjectName(QStringLiteral("switchBtn"));
        switchBtn->setGeometry(QRect(710, 440, 81, 27));
        stackedWidget->addWidget(home);
        setting = new QWidget();
        setting->setObjectName(QStringLiteral("setting"));
        largeMotorPort = new QLineEdit(setting);
        largeMotorPort->setObjectName(QStringLiteral("largeMotorPort"));
        largeMotorPort->setGeometry(QRect(540, 250, 81, 27));
        motorIp = new QLineEdit(setting);
        motorIp->setObjectName(QStringLiteral("motorIp"));
        motorIp->setGeometry(QRect(290, 200, 241, 27));
        videoUrl2 = new QLineEdit(setting);
        videoUrl2->setObjectName(QStringLiteral("videoUrl2"));
        videoUrl2->setGeometry(QRect(290, 150, 331, 27));
        largeMotorIp = new QLineEdit(setting);
        largeMotorIp->setObjectName(QStringLiteral("largeMotorIp"));
        largeMotorIp->setGeometry(QRect(290, 250, 241, 27));
        motorPort = new QLineEdit(setting);
        motorPort->setObjectName(QStringLiteral("motorPort"));
        motorPort->setGeometry(QRect(540, 200, 81, 27));
        label_motor1 = new QLabel(setting);
        label_motor1->setObjectName(QStringLiteral("label_motor1"));
        label_motor1->setGeometry(QRect(230, 200, 61, 21));
        label_motor2 = new QLabel(setting);
        label_motor2->setObjectName(QStringLiteral("label_motor2"));
        label_motor2->setGeometry(QRect(230, 250, 61, 21));
        label_rtsp2 = new QLabel(setting);
        label_rtsp2->setObjectName(QStringLiteral("label_rtsp2"));
        label_rtsp2->setGeometry(QRect(230, 150, 51, 21));
        videoUrl1 = new QLineEdit(setting);
        videoUrl1->setObjectName(QStringLiteral("videoUrl1"));
        videoUrl1->setGeometry(QRect(290, 100, 331, 27));
        label_rtsp1 = new QLabel(setting);
        label_rtsp1->setObjectName(QStringLiteral("label_rtsp1"));
        label_rtsp1->setGeometry(QRect(230, 100, 51, 21));
        settingsBtn = new QPushButton(setting);
        settingsBtn->setObjectName(QStringLiteral("settingsBtn"));
        settingsBtn->setGeometry(QRect(330, 340, 99, 27));
        checkBoxVideo1 = new QCheckBox(setting);
        checkBoxVideo1->setObjectName(QStringLiteral("checkBoxVideo1"));
        checkBoxVideo1->setGeometry(QRect(630, 100, 21, 22));
        checkBoxVideo2 = new QCheckBox(setting);
        checkBoxVideo2->setObjectName(QStringLiteral("checkBoxVideo2"));
        checkBoxVideo2->setGeometry(QRect(630, 150, 21, 22));
        cancelBtn = new QPushButton(setting);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setGeometry(QRect(460, 340, 99, 27));
        label_motor2_2 = new QLabel(setting);
        label_motor2_2->setObjectName(QStringLiteral("label_motor2_2"));
        label_motor2_2->setGeometry(QRect(230, 290, 61, 21));
        checkBoxCruise = new QCheckBox(setting);
        checkBoxCruise->setObjectName(QStringLiteral("checkBoxCruise"));
        checkBoxCruise->setGeometry(QRect(290, 290, 21, 22));
        stackedWidget->addWidget(setting);
        task = new QWidget();
        task->setObjectName(QStringLiteral("task"));
        tableTask = new QTableView(task);
        tableTask->setObjectName(QStringLiteral("tableTask"));
        tableTask->setGeometry(QRect(20, 40, 831, 431));
        taskAddBtn = new QPushButton(task);
        taskAddBtn->setObjectName(QStringLiteral("taskAddBtn"));
        taskAddBtn->setGeometry(QRect(20, 0, 81, 27));
        taskEditBtn = new QPushButton(task);
        taskEditBtn->setObjectName(QStringLiteral("taskEditBtn"));
        taskEditBtn->setGeometry(QRect(110, 0, 81, 27));
        taskDelBtn = new QPushButton(task);
        taskDelBtn->setObjectName(QStringLiteral("taskDelBtn"));
        taskDelBtn->setGeometry(QRect(200, 0, 81, 27));
        stackedWidget->addWidget(task);
        point = new QWidget();
        point->setObjectName(QStringLiteral("point"));
        tablePoint = new QTableView(point);
        tablePoint->setObjectName(QStringLiteral("tablePoint"));
        tablePoint->setGeometry(QRect(20, 40, 831, 431));
        tablePoint->verticalHeader()->setVisible(false);
        pointDelBtn = new QPushButton(point);
        pointDelBtn->setObjectName(QStringLiteral("pointDelBtn"));
        pointDelBtn->setGeometry(QRect(200, 0, 81, 27));
        pointEditBtn = new QPushButton(point);
        pointEditBtn->setObjectName(QStringLiteral("pointEditBtn"));
        pointEditBtn->setGeometry(QRect(110, 0, 81, 27));
        pointAddBtn = new QPushButton(point);
        pointAddBtn->setObjectName(QStringLiteral("pointAddBtn"));
        pointAddBtn->setGeometry(QRect(20, 0, 81, 27));
        stackedWidget->addWidget(point);
        report = new QWidget();
        report->setObjectName(QStringLiteral("report"));
        report_export_2 = new QPushButton(report);
        report_export_2->setObjectName(QStringLiteral("report_export_2"));
        report_export_2->setGeometry(QRect(20, 0, 99, 27));
        label_normal_2 = new QLabel(report);
        label_normal_2->setObjectName(QStringLiteral("label_normal_2"));
        label_normal_2->setGeometry(QRect(150, 2, 31, 21));
        task_enable_4 = new QCheckBox(report);
        task_enable_4->setObjectName(QStringLiteral("task_enable_4"));
        task_enable_4->setGeometry(QRect(170, 2, 21, 22));
        tableReport = new QTableView(report);
        tableReport->setObjectName(QStringLiteral("tableReport"));
        tableReport->setGeometry(QRect(20, 40, 831, 431));
        stackedWidget->addWidget(report);
        taskedit = new QWidget();
        taskedit->setObjectName(QStringLiteral("taskedit"));
        taskSaveBtn = new QPushButton(taskedit);
        taskSaveBtn->setObjectName(QStringLiteral("taskSaveBtn"));
        taskSaveBtn->setGeometry(QRect(380, 430, 99, 27));
        label_task_name_6 = new QLabel(taskedit);
        label_task_name_6->setObjectName(QStringLiteral("label_task_name_6"));
        label_task_name_6->setGeometry(QRect(60, 30, 61, 21));
        taskName = new QLineEdit(taskedit);
        taskName->setObjectName(QStringLiteral("taskName"));
        taskName->setGeometry(QRect(130, 100, 200, 27));
        label_motor2_4 = new QLabel(taskedit);
        label_motor2_4->setObjectName(QStringLiteral("label_motor2_4"));
        label_motor2_4->setGeometry(QRect(60, 70, 61, 21));
        taskEnable = new QCheckBox(taskedit);
        taskEnable->setObjectName(QStringLiteral("taskEnable"));
        taskEnable->setGeometry(QRect(130, 70, 21, 22));
        taskTime = new QTimeEdit(taskedit);
        taskTime->setObjectName(QStringLiteral("taskTime"));
        taskTime->setGeometry(QRect(130, 30, 200, 27));
        taskTime->setMinimumTime(QTime(0, 0, 0));
        taskTime->setTime(QTime(8, 0, 0));
        stackedWidget->addWidget(taskedit);
        pointedit = new QWidget();
        pointedit->setObjectName(QStringLiteral("pointedit"));
        label_task_name = new QLabel(pointedit);
        label_task_name->setObjectName(QStringLiteral("label_task_name"));
        label_task_name->setGeometry(QRect(65, 34, 41, 21));
        pointMotor = new QLineEdit(pointedit);
        pointMotor->setObjectName(QStringLiteral("pointMotor"));
        pointMotor->setGeometry(QRect(130, 70, 200, 27));
        pointMotor->setReadOnly(true);
        label_task_name_5 = new QLabel(pointedit);
        label_task_name_5->setObjectName(QStringLiteral("label_task_name_5"));
        label_task_name_5->setGeometry(QRect(60, 72, 61, 21));
        pointImage = new QLabel(pointedit);
        pointImage->setObjectName(QStringLiteral("pointImage"));
        pointImage->setGeometry(QRect(460, 32, 320, 240));
        pointImageArea = new QLineEdit(pointedit);
        pointImageArea->setObjectName(QStringLiteral("pointImageArea"));
        pointImageArea->setGeometry(QRect(130, 110, 200, 27));
        pointImageArea->setReadOnly(true);
        label_task_name_8 = new QLabel(pointedit);
        label_task_name_8->setObjectName(QStringLiteral("label_task_name_8"));
        label_task_name_8->setGeometry(QRect(60, 112, 61, 21));
        pointSaveBtn = new QPushButton(pointedit);
        pointSaveBtn->setObjectName(QStringLiteral("pointSaveBtn"));
        pointSaveBtn->setGeometry(QRect(380, 430, 99, 27));
        keyPoint = new QCheckBox(pointedit);
        keyPoint->setObjectName(QStringLiteral("keyPoint"));
        keyPoint->setGeometry(QRect(130, 150, 21, 22));
        label_motor2_3 = new QLabel(pointedit);
        label_motor2_3->setObjectName(QStringLiteral("label_motor2_3"));
        label_motor2_3->setGeometry(QRect(40, 150, 71, 21));
        loadConfigBtn = new QPushButton(pointedit);
        loadConfigBtn->setObjectName(QStringLiteral("loadConfigBtn"));
        loadConfigBtn->setGeometry(QRect(460, 290, 111, 27));
        pointNum = new QSpinBox(pointedit);
        pointNum->setObjectName(QStringLiteral("pointNum"));
        pointNum->setGeometry(QRect(130, 32, 200, 27));
        pointNum->setMinimum(1);
        pointNum->setMaximum(200);
        stackedWidget->addWidget(pointedit);
        homeBtn = new QPushButton(centralWidget);
        homeBtn->setObjectName(QStringLiteral("homeBtn"));
        homeBtn->setGeometry(QRect(0, 0, 51, 27));
        settingBtn = new QPushButton(centralWidget);
        settingBtn->setObjectName(QStringLiteral("settingBtn"));
        settingBtn->setGeometry(QRect(70, 0, 61, 27));
        taskBtn = new QPushButton(centralWidget);
        taskBtn->setObjectName(QStringLiteral("taskBtn"));
        taskBtn->setGeometry(QRect(150, 0, 41, 27));
        reportBtn = new QPushButton(centralWidget);
        reportBtn->setObjectName(QStringLiteral("reportBtn"));
        reportBtn->setGeometry(QRect(270, 0, 51, 27));
        pointBtn = new QPushButton(centralWidget);
        pointBtn->setObjectName(QStringLiteral("pointBtn"));
        pointBtn->setGeometry(QRect(210, 0, 41, 27));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);
        ctrlpanel->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Camera", 0));
        actionHome->setText(QApplication::translate("MainWindow", "Home", 0));
        actionSetting->setText(QApplication::translate("MainWindow", "Setting", 0));
        login_name->setPlaceholderText(QApplication::translate("MainWindow", "name", 0));
        login_passwd->setPlaceholderText(QApplication::translate("MainWindow", "password", 0));
        login_btn->setText(QApplication::translate("MainWindow", "login", 0));
        login_avatar->setText(QString());
        image1->setText(QApplication::translate("MainWindow", "screenshot1", 0));
        video1->setText(QApplication::translate("MainWindow", "video1", 0));
        video2->setText(QApplication::translate("MainWindow", "video2", 0));
        image2->setText(QApplication::translate("MainWindow", "screenshot2", 0));
        screenshot->setText(QApplication::translate("MainWindow", "screenshot", 0));
        screenshotRightBtn->setText(QApplication::translate("MainWindow", "right", 0));
        m2LeftBtn->setText(QApplication::translate("MainWindow", "m2 left", 0));
        screenshotLeftBtn->setText(QApplication::translate("MainWindow", "left", 0));
        m4LeftBtn->setText(QApplication::translate("MainWindow", "m4 left", 0));
        m3LeftBtn->setText(QApplication::translate("MainWindow", "m3 left", 0));
        m4RightBtn->setText(QApplication::translate("MainWindow", "m4 right", 0));
        motorUpBtn->setText(QApplication::translate("MainWindow", "up", 0));
        m2RightBtn->setText(QApplication::translate("MainWindow", "m2 right", 0));
        m1RightBtn->setText(QApplication::translate("MainWindow", "m1 right", 0));
        mnStopBtn->setText(QApplication::translate("MainWindow", "stop", 0));
        motor2->setText(QApplication::translate("MainWindow", "motor2", 0));
        motorLeftBtn->setText(QApplication::translate("MainWindow", "left", 0));
        motorRightBtn->setText(QApplication::translate("MainWindow", "right", 0));
        motor1->setText(QApplication::translate("MainWindow", "motor1", 0));
        m1LeftBtn->setText(QApplication::translate("MainWindow", "m1 left", 0));
        motorDownBtn->setText(QApplication::translate("MainWindow", "down", 0));
        m3RightBtn->setText(QApplication::translate("MainWindow", "m3 right", 0));
        addPointBtn->setText(QApplication::translate("MainWindow", "add point", 0));
        shortcut->setText(QApplication::translate("MainWindow", "shortcut", 0));
        mnResetBtn->setText(QApplication::translate("MainWindow", "reset", 0));
        labelpath->setText(QApplication::translate("MainWindow", "path", 0));
        switchBtn->setText(QApplication::translate("MainWindow", "switch", 0));
        largeMotorPort->setText(QApplication::translate("MainWindow", "10086", 0));
        largeMotorPort->setPlaceholderText(QApplication::translate("MainWindow", "PORT", 0));
        motorIp->setText(QApplication::translate("MainWindow", "192.168.1.108", 0));
        motorIp->setPlaceholderText(QApplication::translate("MainWindow", "IP", 0));
        videoUrl2->setText(QApplication::translate("MainWindow", "rtsp://192.168.1.108:554/snl/live/1/1", 0));
        videoUrl2->setPlaceholderText(QApplication::translate("MainWindow", "URL", 0));
        largeMotorIp->setText(QApplication::translate("MainWindow", "192.168.1.104", 0));
        largeMotorIp->setPlaceholderText(QApplication::translate("MainWindow", "IP", 0));
        motorPort->setText(QApplication::translate("MainWindow", "30001", 0));
        motorPort->setPlaceholderText(QApplication::translate("MainWindow", "PORT", 0));
        label_motor1->setText(QApplication::translate("MainWindow", "motor1", 0));
        label_motor2->setText(QApplication::translate("MainWindow", "motor2", 0));
        label_rtsp2->setText(QApplication::translate("MainWindow", "video2", 0));
        videoUrl1->setText(QApplication::translate("MainWindow", "rtsp://192.168.1.108:554/snl/live/1/1", 0));
        videoUrl1->setPlaceholderText(QApplication::translate("MainWindow", "URL", 0));
        label_rtsp1->setText(QApplication::translate("MainWindow", "video1", 0));
        settingsBtn->setText(QApplication::translate("MainWindow", "Save", 0));
        checkBoxVideo1->setText(QString());
        checkBoxVideo2->setText(QString());
        cancelBtn->setText(QApplication::translate("MainWindow", "Cancel", 0));
        label_motor2_2->setText(QApplication::translate("MainWindow", "cruise", 0));
        checkBoxCruise->setText(QString());
        taskAddBtn->setText(QApplication::translate("MainWindow", "add", 0));
        taskEditBtn->setText(QApplication::translate("MainWindow", "edit", 0));
        taskDelBtn->setText(QApplication::translate("MainWindow", "delete", 0));
        pointDelBtn->setText(QApplication::translate("MainWindow", "delete", 0));
        pointEditBtn->setText(QApplication::translate("MainWindow", "edit", 0));
        pointAddBtn->setText(QApplication::translate("MainWindow", "add", 0));
        report_export_2->setText(QApplication::translate("MainWindow", "export", 0));
        label_normal_2->setText(QApplication::translate("MainWindow", "all", 0));
        task_enable_4->setText(QString());
        taskSaveBtn->setText(QApplication::translate("MainWindow", "Save", 0));
        label_task_name_6->setText(QApplication::translate("MainWindow", "time", 0));
        taskName->setText(QString());
        taskName->setPlaceholderText(QApplication::translate("MainWindow", "task name", 0));
        label_motor2_4->setText(QApplication::translate("MainWindow", "enable", 0));
        taskEnable->setText(QString());
        taskTime->setDisplayFormat(QApplication::translate("MainWindow", "hh:mm", 0));
        label_task_name->setText(QApplication::translate("MainWindow", "point", 0));
        pointMotor->setText(QString());
        pointMotor->setPlaceholderText(QApplication::translate("MainWindow", "motor", 0));
        label_task_name_5->setText(QApplication::translate("MainWindow", "motor", 0));
        pointImage->setText(QApplication::translate("MainWindow", "Image", 0));
        pointImageArea->setText(QString());
        pointImageArea->setPlaceholderText(QApplication::translate("MainWindow", "image", 0));
        label_task_name_8->setText(QApplication::translate("MainWindow", "image", 0));
        pointSaveBtn->setText(QApplication::translate("MainWindow", "Save", 0));
        keyPoint->setText(QString());
        label_motor2_3->setText(QApplication::translate("MainWindow", "key point", 0));
        loadConfigBtn->setText(QApplication::translate("MainWindow", "Load Config", 0));
        homeBtn->setText(QApplication::translate("MainWindow", "home", 0));
        settingBtn->setText(QApplication::translate("MainWindow", "setting", 0));
        taskBtn->setText(QApplication::translate("MainWindow", "task", 0));
        reportBtn->setText(QApplication::translate("MainWindow", "report", 0));
        pointBtn->setText(QApplication::translate("MainWindow", "point", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
