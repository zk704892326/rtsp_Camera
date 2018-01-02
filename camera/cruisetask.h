#ifndef CRUISETASK_H
#define CRUISETASK_H
#include <QObject>
#include <QThread>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <QDebug>
#include <QTime>
#include <QLabel>
#include "ele_mach.h"
#include "largemotor.h"
#include "common.h"

typedef struct Task_t {
    QString name;
    QDateTime date;
} Task_t;

typedef struct Point_t {
    QString name;
    QString motor;
    QString img_path;
    QString img_area;
    QString key_point;
} Point_t;

class CruiseTask : public QThread
{
    Q_OBJECT
public:
    QString host;
    int port;
    QLabel *label;
    //LargeMotor largeMotor;
    explicit CruiseTask();
    ~CruiseTask();
    void play();
    void stop();
    void run();
    void loadConfig(Settings_t *settings);
    void loadtask();

private:
    bool started;
    bool restart;
    bool stoped;
    QVector<Task_t> tasks;
    QVector<Point_t> points;
    Settings_t *settings;
    QTimer *taskTimer;
    Ele_mach *ele_mach;
    QTcpSocket *taskSock;
    QDateTime date;
    int imgIndex;

private slots:
    void onTaskTimer();
};

#endif // CRUISETASK_H
