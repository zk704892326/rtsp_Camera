#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDebug>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new Sqlite3();
    if(db->open("example.db")) {
        QSqlQuery *query = new QSqlQuery(
                        "CREATE TABLE IF NOT EXISTS users "
                        "("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "name TEXT UNIQUE NOT NULL, "
                            "age INTEGER, "
                            "time TEXT NOT NULL"
                        ")"
                    );
        if(!query->exec()) {
            qDebug()<<db->lastError();
        }
//        query->prepare("INSERT INTO users (name, age, time) VALUES (:name, :age, datetime('now'));");
//        query->bindValue(":name", "xiaohong");
//        query->bindValue(":age", 12);
//        if(!query->exec()) {
//            qDebug()<<db->lastError();
//        }
        delete query;

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(QString("select name, age, time from users;"));
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("name"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("age"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("time"));
        ui->tableView->setModel(model);
        db->close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
