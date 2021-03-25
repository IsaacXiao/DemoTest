#ifndef DEMO2_PUSHBUTTON_H
#define DEMO2_PUSHBUTTON_H
#include <QPushButton>
#include <QPaintEvent>
#include <QMouseEvent>

#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QRect>

enum DIRECTION{BTN_LEFT,BTN_RIGHT};

template<int v>
struct Int2Type
{
    enum { value = v };
};

template<DIRECTION d>
class DemoPushButton : public QPushButton
{
private:
	bool israised;
    enum{direction=d};
public:
    DemoPushButton(QWidget *parent=NULL)
        :QPushButton(parent),israised(true)
    {
        setMouseTracking(true);
    }
protected:
    void display(Int2Type<BTN_LEFT>,QPainter & painter)
    {
        QPoint left(0,height()/2);
        QPoint triangle[3] = {left,rect().topRight(),rect().bottomRight()};

        painter.drawPolygon(triangle,3);
    }
    void display(Int2Type<BTN_RIGHT>,QPainter & painter)
    {
        QPoint right(width(),height()/2);
        QPoint triangle[3] = {right,rect().topLeft(),rect().bottomLeft()};

        painter.drawPolygon(triangle,3);
    }
    virtual void paintEvent(QPaintEvent *e)
    {
        QPainter painter(this);

        QColor prominent(210,180,140);
        QColor highlight(205,0,0);
        QBrush b1(prominent);
        QBrush b2(highlight);

        if(israised)
        {
            painter.setBrush(b1);
        }
        else
        {
            painter.setBrush(b2);
        }

        display(Int2Type<this->direction>(),painter);
    }

    virtual void enterEvent(QEvent *e)
    {
        israised=false;
        repaint();
    }
    virtual void leaveEvent(QEvent *e)
    {
        israised=true;
        repaint();
    }
    virtual void mouseMoveEvent(QMouseEvent *e)
    {
        float w=width();
        float h=height();
        int x=e->x();
        int y=e->y();
        float k=h/w;

        if(	y>=-k*x+h/2 &&
                y>= k*x-h/2	&&
                y<= k*x+h/2 &&
                y<=-k*x+3*h/2)
        {
            israised=false;
        }
        else
        {
            israised=true;
        }
        repaint();
    }
};
#endif
