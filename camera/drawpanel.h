#ifndef DRAWPANEL_H
#define DRAWPANEL_H
#include <QtWidgets/QLabel>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

class DrawPanel : public QLabel
{
    Q_OBJECT
public:
    explicit DrawPanel(QWidget *parent=0);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void setRect(const QRect &rect);

signals:
    void GetRect(const QRect &rect);

private:
    QPoint point0;
    QPoint point1;
    QRect rect;
};

#endif // DRAWPANEL_H
