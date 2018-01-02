#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    if(argc >= 5){
        loginnamecmd = argv[1];
        if(loginnamecmd == "-u"){
            loginname = argv[2];
        }

        loginpasscmd = argv[3];
        if(loginpasscmd == "-p"){
            loginpass = argv[4];
        }
    }

    qDebug()<<loginnamecmd<<loginname<<loginpasscmd<<loginpass<<endl;

    QApplication a(argc, argv);
    MainWindow w;

    QFile qssFile(":/style.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen()){
        qApp->setStyleSheet(QLatin1String(qssFile.readAll()));
        qssFile.close();
    }

    w.setFixedSize(w.width(),w.height());
    w.move ((QApplication::desktop()->width() - w.width())/2,
            (QApplication::desktop()->height() - w.height())/2);
    w.show();

    return a.exec();
}
