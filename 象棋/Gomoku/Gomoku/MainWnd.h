#ifndef MAINWND_H
#define MAINWND_H


#include <QWidget>

#include <DemoPushButton.hpp>

//#include <QMainWindow>
//不要让它从QMainWindow继承，因为默认layout会妨碍自定义布局显示，写起来麻烦
class MainWnd : public QWidget
{
    Q_OBJECT
private:
    DemoPushButton<BTN_RIGHT>* forward;
    DemoPushButton<BTN_LEFT>* backward;
    size_t _gameType;
public:
    explicit MainWnd(size_t gameType, QWidget *parent = 0);
    ~MainWnd();

signals:

public slots:
};

#endif // MAINWND_H
