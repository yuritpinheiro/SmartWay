#include "smartway.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SmartWay w;
    w.show();

    return a.exec();
}
