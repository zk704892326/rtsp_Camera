#include <QPainter>
#include <QWidget>
#include <QPen>
#include "paintlabel.h"

PaintLabel::PaintLabel(QWidget *parent):QLabel(parent)
{
    pointx = 100;
    pointy = 100;
}
void PaintLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::green, 1));
    painter.setBrush(Qt::green);
    if(this->width()==480){
        painter.drawEllipse(pointx, pointx, 10, 10);
    }else{
        painter.drawEllipse(pointx*2, pointx*2, 10, 10);
    }

    QLabel::paintEvent(event);
}

void PaintLabel::updatePointInfo(quint32 newpointx, quint32 newpointy)
{
    if(newpointx<0){
        pointx = 0;
    }else if(newpointx>480){
       pointx = 480;
    }else{
        pointx = newpointx;
    }

    if(newpointy<0){
        pointy = 0;
    }else if(newpointy>360){
       pointy = 360;
    }else{
        pointy = newpointy;
    }

    update();
}
