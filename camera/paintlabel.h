#ifndef PAINTLABEL
#define PAINTLABEL

#include <QLabel>

class PaintLabel:public QLabel
{
    Q_OBJECT
public:
    explicit PaintLabel(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void updatePointInfo(quint32 newpointx, quint32 newpointy);
private:
    quint32 pointx;
    quint32 pointy;
};

#endif // PAINTLABEL

