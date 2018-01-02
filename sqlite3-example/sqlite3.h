#ifndef SQLITE3_H
#define SQLITE3_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Sqlite3 : public QObject
{
    Q_OBJECT
public:
    explicit Sqlite3();
    ~Sqlite3();
    bool open(QString url);
    bool close();
    QSqlDatabase &instance();
    QSqlError lastError();

signals:

public slots:

private:
    QSqlDatabase db;
};

#endif // SQLITE3_H
