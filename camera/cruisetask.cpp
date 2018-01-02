#include "cruisetask.h"

CruiseTask::CruiseTask()
{
    started = false;
    restart = false;
    stoped = false;
    imgIndex = 0;
}

CruiseTask::~CruiseTask() {

}

void CruiseTask::play() {
    if(!started) {
        started = true;
        start();
    } else {
        restart = true;
    }
    stoped = false;
}

void CruiseTask::stop() {
    stoped = true;
}

void CruiseTask::run() {
    loadtask();
    ele_mach = new Ele_mach();
    ele_mach->set_Camera_config(this->settings->motors[0].ip,this->settings->motors[0].port);
    taskTimer = new QTimer();
    connect(taskTimer, SIGNAL(timeout()), this, SLOT(onTaskTimer()), Qt::DirectConnection);
    taskTimer->start(10000);
    exec();
}

void CruiseTask::loadtask() {
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_PATH);
    if(!db.open()) {
        qDebug()<<db.lastError();
    } else {
//        qDebug()<<"db open success";
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM tasks ORDER BY time ASC;");
    if(!query.exec()) {
        qDebug()<<db.lastError();
    }
    tasks.clear();
    for( int r=0; query.next(); r++ ) {
        QTime time0 = QTime::fromString(query.value(1).toString());
        QDateTime date0 = QDateTime::currentDateTime();
        QDateTime date1 = date0;
        date0.setTime(time0);
        if(date1 > date0) {
            date0 = date0.addDays(1);
        }
        qDebug()<<date0;
        Task_t Task = {query.value(1).toString(), date0};
        tasks.append(Task);
    }

    query.prepare("SELECT * FROM points ORDER BY name ASC;");
    if(!query.exec()) {
        qDebug()<<db.lastError();
    }
    points.clear();
    for( int r=0; query.next(); r++ ) {
        Point_t Point = {query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString()};
        points.append(Point);
    }
    db.close();
}

void CruiseTask::loadConfig(Settings_t *settings) {
    this->settings = settings;
}

void CruiseTask::onTaskTimer() {
    if(stoped) {
        return;
    }
    if(restart) {
        loadtask();
        restart = false;
    }
    int x0=0, x1=0, x2=0, x3=0, x7=0;
    float x4=0, x5=0, x6=0;
    date = QDateTime::currentDateTime();
    for (int i = 0; i < tasks.size(); ++i)
    {
        if(abs(date.secsTo(tasks[i].date)) < 60) {
            tasks[i].date = tasks[i].date.addDays(1);
            for(int j = 0; j < points.size(); ++j) {
                sscanf(points[j].motor.toStdString().c_str(), "%d,%d,%d,%d,%f,%f,%f,%d", &x0, &x1, &x2, &x3, &x4, &x5, &x6, &x7);
                qDebug()<<tasks[i].name<<points[j].name<<points[j].motor<<date;
                qDebug()<<x0<<x1<<x2<<x3<<x4<<x5<<x6<<x7;
                ele_mach->send_message_to_Mach(x0,x1,x2,x3,x4,x5,x6,x7,settings->motors[1].ip, settings->motors[1].port);
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100000);
                if(label->pixmap()) {
                    label->pixmap()->save(QString(IMG_DIR) + "/record" + QString::number(imgIndex) + ".png");
                }

                QSqlDatabase db;
                if(QSqlDatabase::contains("qt_sql_default_connection"))
                  db = QSqlDatabase::database("qt_sql_default_connection");
                else
                  db = QSqlDatabase::addDatabase("QSQLITE");
                db.setDatabaseName(DB_PATH);
                if(!db.open()) {
                    qDebug()<<db.lastError();
                } else {
            //        qDebug()<<"db open success";
                }

                QDateTime date0 = QDateTime::currentDateTime();
                QSqlQuery query;
                query.prepare("INSERT INTO records (time, point, state, img_path) VALUES (:time, :point, :state, :img_path);");
                query.bindValue(0, date0.toString("yyyy-MM-dd hh:mm:ss"));
                query.bindValue(1, points[j].name);
                query.bindValue(2, "ok");
                query.bindValue(3, QString(IMG_DIR) + "/record" + QString::number(imgIndex) + ".png");
                ++imgIndex;
                if(!query.exec()) {
                    qDebug()<<db.lastError();
                }
                db.commit();
                db.close();
                qDebug()<<x0<<x1<<x2<<x3<<x4<<x5<<"ok";
            }
        }
    }
}

