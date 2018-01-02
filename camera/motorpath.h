#ifndef MOTORPATH_H
#define MOTORPATH_H
#include <QtWidgets/QLabel>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

class MotorPath : public QLabel
{
public:
    MotorPath(QWidget *parent=0);
    void paintEvent(QPaintEvent*);
};

#endif // MOTORPATH_H
