#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //https://blog.csdn.net/douzhq/article/details/84933222
    ImageView localScaleWidget;
    localScaleWidget.show();
    return a.exec();
}
