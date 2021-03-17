#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QPaintEvent>


class LocalScaleWidget : public QWidget
{
     Q_OBJECT
     public:
          LocalScaleWidget(QWidget *parent=0);
          ~LocalScaleWidget();
     public:
          void paintEvent(QPaintEvent *e);
          void mouseMoveEvent(QMouseEvent *event);
     private:
          int x,y;
          int width,height;
          QPixmap pixmap;
          QPixmap mypixmap ;
          QPixmap background;
};

#endif // WIDGET_H
