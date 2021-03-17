#include "widget.h"


#include <QPainter>
#include <QPoint>
#include <QEvent>
#include <QtGui>
#include <QMouseEvent>

LocalScaleWidget::LocalScaleWidget(QWidget *parent):QWidget(parent)
{
     setMouseTracking(true);
     background.load("D:/WorkSpace/Inspection/Images/TBA10-23-14-28-54-956-2366.bmp");
     this->adjustSize();
     this->setMinimumSize(800,600);
}

LocalScaleWidget::~LocalScaleWidget()
{
}

void LocalScaleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,background);
    painter.drawPixmap(x+20,y+20,pixmap);
}

void LocalScaleWidget::mouseMoveEvent(QMouseEvent *event)
{
    x = event->x();
    y = event->y();
    mypixmap = mypixmap.grabWidget(this,x,y,30,30);
    width = mypixmap.width();
    height = mypixmap.height();
    pixmap = mypixmap.scaled(width * 5,height * 5,Qt::KeepAspectRatio);
    update();
}

