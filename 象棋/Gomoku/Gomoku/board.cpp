#include "board.h"
#include <iterator>
#include <QtAlgorithms>
#include <algorithm>
#include <QMessageBox>

Board::Board(QWidget*parent):QFrame(parent)
{
    std::back_inserter(stones) = new Stone("车",Qt::black,true,false,20,1,1);
    std::back_inserter(stones )= new Stone("马",Qt::black,true,false,20,1,2);
    std::back_inserter(stones) = new Stone("象",Qt::black,true,false,20,1,3);
    std::back_inserter(stones) = new Stone("士",Qt::black,true,false,20,1,4);
    std::back_inserter(stones) = new Stone("将",Qt::black,true,false,20,1,5);
    std::back_inserter(stones) = new Stone("士",Qt::black,true,false,20,1,6);
    std::back_inserter(stones) = new Stone("象",Qt::black,true,false,20,1,7);
    std::back_inserter(stones) = new Stone("马",Qt::black,true,false,20,1,8);
    std::back_inserter(stones) = new Stone("车",Qt::black,true,false,20,1,9);

    std::back_inserter(stones) = new Stone("炮",Qt::black,true,false,20,3,2);
    std::back_inserter(stones) = new Stone("炮",Qt::black,true,false,20,3,8);

    std::back_inserter(stones) = new Stone("卒",Qt::black,true,false,20,4,1);
    std::back_inserter(stones) = new Stone("卒",Qt::black,true,false,20,4,3);
    std::back_inserter(stones) = new Stone("卒",Qt::black,true,false,20,4,5);
    std::back_inserter(stones) = new Stone("卒",Qt::black,true,false,20,4,7);
    std::back_inserter(stones) = new Stone("卒",Qt::black,true,false,20,4,9);


    std::back_inserter(stones) = new Stone("车",Qt::red,true,false,20,10,1);
    std::back_inserter(stones) = new Stone("马",Qt::red,true,false,20,10,2);
    std::back_inserter(stones) = new Stone("象",Qt::red,true,false,20,10,3);
    std::back_inserter(stones) = new Stone("士",Qt::red,true,false,20,10,4);
    std::back_inserter(stones) = new Stone("将",Qt::red,true,false,20,10,5);
    std::back_inserter(stones) = new Stone("士",Qt::red,true,false,20,10,6);
    std::back_inserter(stones) = new Stone("象",Qt::red,true,false,20,10,7);
    std::back_inserter(stones) = new Stone("马",Qt::red,true,false,20,10,8);
    std::back_inserter(stones) = new Stone("车",Qt::red,true,false,20,10,9);

    std::back_inserter(stones) = new Stone("炮",Qt::red,true,false,20,8,2);
    std::back_inserter(stones) = new Stone("炮",Qt::red,true,false,20,8,8);

    std::back_inserter(stones) = new Stone("卒",Qt::red,true,false,20,7,1);
    std::back_inserter(stones) = new Stone("卒",Qt::red,true,false,20,7,3);
    std::back_inserter(stones) = new Stone("卒",Qt::red,true,false,20,7,5);
    std::back_inserter(stones) = new Stone("卒",Qt::red,true,false,20,7,7);
    std::back_inserter(stones) = new Stone("卒",Qt::red,true,false,20,7,9);

    setMinimumSize(20*25+1, 20*30+1);
}

Board::~Board()
{
    qDeleteAll(stones.begin(),stones.end());
}

void Board::paintEvent(QPaintEvent*pe)
{
    grid = height()/12;

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));

    // 画10横线
    for(int i=1; i<=10; ++i)
    {
        painter.drawLine(QPoint(grid, i*grid), QPoint(9*grid, i*grid));
    }

    // 画9竖线
    for(int i=1; i<=9; ++i)
    {
        if(i==1 || i==9)
           painter.drawLine(QPoint(i*grid, grid), QPoint(i*grid, 10*grid));
        else
        {
           painter.drawLine(QPoint(i*grid, grid), QPoint(i*grid, 5*grid));
           painter.drawLine(QPoint(i*grid, 6*grid), QPoint(i*grid, 10*grid));
        }
    }
    // 九宫格
    painter.drawLine(QPoint(4*grid, 1*grid), QPoint(6*grid, 3*grid));
    painter.drawLine(QPoint(6*grid, 1*grid), QPoint(4*grid, 3*grid));

    painter.drawLine(QPoint(4*grid, 8*grid), QPoint(6*grid, 10*grid));
    painter.drawLine(QPoint(6*grid, 8*grid), QPoint(4*grid, 10*grid));

    DrawConer(3,2,0);
    DrawConer(3,8,0);
    DrawConer(4,1,1);
    DrawConer(4,3,0);
    DrawConer(4,5,0);
    DrawConer(4,7,0);
    DrawConer(4,9,2);
    DrawConer(8,2,0);
    DrawConer(8,8,0);
    DrawConer(7,1,1);
    DrawConer(7,3,0);
    DrawConer(7,5,0);
    DrawConer(7,7,0);
    DrawConer(7,9,2);

    DrawStone();
}

void Board::DrawConer(size_t row, size_t col, size_t type)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));

    if(type==0 || type==1)
    {
        //|_
        painter.drawLine(QPoint(col*grid+3,row*grid-10),QPoint(col*grid+3,row*grid-3));
        painter.drawLine(QPoint(col*grid+3,row*grid-3),QPoint(col*grid+10,row*grid-3));
        //|-
        painter.drawLine(QPoint(col*grid+3,row*grid+10),QPoint(col*grid+3,row*grid+3));
        painter.drawLine(QPoint(col*grid+3,row*grid+3),QPoint(col*grid+10,row*grid+3));
    }
    if(type==0 || type==2)
    {
        //_|
        painter.drawLine(QPoint(col*grid-3,row*grid-10),QPoint(col*grid-3,row*grid-3));
        painter.drawLine(QPoint(col*grid-3,row*grid-3),QPoint(col*grid-10,row*grid-3));
        //-|
        painter.drawLine(QPoint(col*grid-3,row*grid+3),QPoint(col*grid-10,row*grid+3));
        painter.drawLine(QPoint(col*grid-3,row*grid+3),QPoint(col*grid-3,row*grid+10));
    }
}

void Board::DrawStone()
{
    QPainter painter(this);

    for(auto stone_:stones)
    {
        if(stone_->Appear())
        {
            painter.setPen(QPen(QBrush(stone_->Colour()), 2));

            if(stone_->Selected()) painter.setBrush(Qt::gray);
            else painter.setBrush(Qt::yellow);

            stone_->SetArea(grid/15,grid);

            painter.drawEllipse(stone_->GetArea());
            painter.setFont(QFont("system", stone_->Radius()*1.2, 700));
            painter.drawText(stone_->GetArea(),stone_->Name(),QTextOption(Qt::AlignCenter));
        }
    }
}

void Board::mouseReleaseEvent(QMouseEvent*ev)
{
    if(ev->button() != Qt::LeftButton)
    {
        return;
    }

    const QPoint& position = ev->pos();
    auto hit = std::find_if(stones.begin(),stones.end(),
    [&position](Stone* s) -> bool
    {
        return s->GetArea().contains(position,true);
    });

    if(stones.end()!=hit)  //如果鼠标点中了某个棋子
    {
        auto former_selected = std::find_if(stones.begin(),stones.end(),
        [](Stone* s) -> bool
        {
            return s->Selected();
        });

        if(stones.end()!=former_selected)//如果之前已经有个被选中
        {
            //则把它的选中状态置反
            (*former_selected)->Selected(true);
        }

        (*hit)->Selected(true);
        repaint();
    }
}


