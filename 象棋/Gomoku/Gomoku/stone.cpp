#include "stone.h"
#include <QPen>
#include <QBrush>
#include <QSize>

Stone::Stone(const QString& what, Qt::GlobalColor colour, bool show,
             bool current, size_t r,size_t hang,size_t lie,QObject *parent) :
    name(what),color(colour),appear(show),selected(current),radius(r),row(hang),col(lie),QObject(parent)
{

}

void Stone::SetArea(size_t offset, size_t grid)
{
    QPoint point;
    point.rx()=offset+(col-0.5)*grid;
    point.ry()=offset+(row-0.5)*grid;

    radius=grid/2.3;
    area = QRect(point, QSize(radius*2-1, radius*2-1));
}

bool Stone::Selected(bool modifiy)
{
    if(modifiy)
    {
        selected=!selected;
    }

    return selected;
}




