#include "MainWnd.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QStatusBar>
#include "board.h"

MainWnd::MainWnd(size_t gameType, QWidget *parent) : QWidget(parent)
{
    _gameType = gameType;

    Board * board = new Board;

    forward = new DemoPushButton<BTN_RIGHT>();
    backward = new DemoPushButton<BTN_LEFT>();

    QLabel* chat_label = new QLabel("聊天记录");
    QTextEdit* chat_record = new QTextEdit(this);
    QLineEdit* chat_msg = new QLineEdit(this);
    //在layout里的widget改变大小无效https://bbs.csdn.net/topics/390005881
    //chat_record->resize(backward->width()*2+20,forward->height()*2.5);
    QStatusBar* hint = new QStatusBar(this);
    QLabel* turn = new QLabel("红方行棋");
    hint->addWidget(turn);

    QHBoxLayout* top_right_ = new QHBoxLayout;
    top_right_->addWidget(backward);
    top_right_->addWidget(forward);

    QVBoxLayout* right_ = new QVBoxLayout;
    right_->addLayout(top_right_);
    right_->addWidget(chat_label);
    right_->addWidget(chat_record);
    right_->addWidget(chat_msg);

    QVBoxLayout* left_ = new QVBoxLayout;
    left_->addWidget(board,1);
    left_->addWidget(hint);

    QHBoxLayout* main_ = new QHBoxLayout(this);
    //QVBoxLayout* v_layout = new QVBoxLayout();
    main_->addLayout(left_);
    main_->addLayout(right_);
}

MainWnd::~MainWnd()
{

}

