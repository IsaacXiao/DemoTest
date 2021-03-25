#ifndef STONE_H
#define STONE_H

#include <QObject>
#include <QPainter>
#include <QColor>
#include <Qt>
#include <QRect>
#include <memory>


class Stone : public QObject
{
    Q_OBJECT
private:
    //enum STONE_TYPE{BING=1, PAO, JU, MA, XIANG, SHI, JIANG};
    //STONE_TYPE type;

    const QString name;
    Qt::GlobalColor color{Qt::red};  //Qt::red或者Qt::black
    bool appear{true};
    bool selected{false};
    size_t radius{20};
    size_t row{0};
    size_t col{0};
    QRect area{QRect(0,0,20,20)};
public:
    const QString Name(){return name;}
    //grid为一个格子的高/宽，这个值是在棋盘WM_PAINT消息时根据其客户区域高度实时计算出来的
    //offset为棋盘最左上角的点距离(0,0)的偏移，也是依赖grid的值按比例调整
    //所以当拖动改变程序的窗口大小时，棋子也能跟着改变大小
    void SetArea(size_t offset,size_t grid);
    const QRect GetArea(){return area;}
    Qt::GlobalColor Colour(){return color;}
    bool Appear(){return appear;}
    bool Selected(bool modifiy=false);
    size_t Radius(){return radius;}

    Stone(const QString& what,Qt::GlobalColor colour,bool show,
                   bool current,size_t r,size_t hang,size_t lie,QObject *parent = nullptr);
    //void Display();
signals:

public slots:
};

#endif // STONE_H
