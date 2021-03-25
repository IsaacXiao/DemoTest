#include <QApplication>

#include "ChooseDlg.h"
//#include "board.h"
#include "MainWnd.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

//    Board board;
//    board.show();
    MainWnd main_wnd(0);
    main_wnd.show();

    return app.exec();
}
