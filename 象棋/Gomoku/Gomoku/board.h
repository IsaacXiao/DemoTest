#ifndef BOARD_H
#define BOARD_H

#include <QFrame>
#include <QPoint>
#include <QVector>
#include <QPainter>
#include <QMouseEvent>


#include "stone.h"

class Board : public QFrame
{
    Q_OBJECT
private:
    size_t grid{20};
    QVector<Stone*> stones;
    void paintEvent(QPaintEvent*pe);
    //画炮和兵的拐角
    void DrawConer(size_t row,size_t col,size_t type);
    void DrawStone();
protected:
    void mouseReleaseEvent(QMouseEvent*ev);
public:
    explicit Board(QWidget*parent=nullptr);
    virtual ~Board();
signals:

public slots:

};

#endif // BOARD_H
