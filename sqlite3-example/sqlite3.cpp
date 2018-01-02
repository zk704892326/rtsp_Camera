#include "sqlite3.h"
#include <qdebug.h>

Sqlite3::Sqlite3()
{

}

Sqlite3::~Sqlite3()
{

}

bool Sqlite3::open(QString url) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(url);
    if(!db.open()) {
        qDebug()<<db.lastError();
        return false;
    } else {
        qDebug()<<"db open success";
    }
    return true;
}

bool Sqlite3::close() {
    if(db.isOpen()) {
        db.close();
        QSqlDatabase::removeDatabase("QSQLITE");
    }
    return true;
}

QSqlDatabase &Sqlite3::instance() {
    return db;
}

QSqlError Sqlite3::lastError() {
    return db.lastError();
}
