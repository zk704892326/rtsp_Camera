#include "motorpath.h"

MotorPath::MotorPath(QWidget *parent): QLabel(parent)
{
}

void MotorPath::paintEvent(QPaintEvent*) {
    QPainter paint(this);
    paint.setPen(QPen(Qt::blue, 1, Qt::DashLine));
    QRect rect = this->geometry();
    rect = QRect(0, 0, rect.width()-1, rect.height()-1);
    qDebug()<<rect<<endl;
    paint.drawRect(rect);

}

