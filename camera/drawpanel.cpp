#include "drawpanel.h"

DrawPanel::DrawPanel(QWidget *parent): QLabel(parent)
{
}

void DrawPanel::mousePressEvent(QMouseEvent *event) {
    point0 = event->pos();
    point1 = point0;
}

void DrawPanel::mouseMoveEvent(QMouseEvent *event) {
    point1 = event->pos();
    update();
}

void DrawPanel::mouseReleaseEvent (QMouseEvent *event)
{
    emit GetRect(rect);
}

void DrawPanel::paintEvent(QPaintEvent*) {
    QPainter paint(this);
    paint.setPen(QPen(Qt::blue, 1, Qt::DashLine));
    rect = QRect(point0, point1);
    paint.drawRect(rect);
}

void DrawPanel::setRect(const QRect &rect) {
    point0.setX(rect.left());
    point0.setY(rect.top());
    point1.setX(rect.left()+rect.width());
    point1.setY(rect.top()+rect.height());
    update();
}

