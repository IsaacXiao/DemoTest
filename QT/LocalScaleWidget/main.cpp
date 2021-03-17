#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ImageView localScaleWidget;
    localScaleWidget.show();
    return a.exec();
}
