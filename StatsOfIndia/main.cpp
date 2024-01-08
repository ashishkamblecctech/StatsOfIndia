#include "stdafx.h"
#include "StatsOfIndia.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StatsOfIndia w;
    w.show();
    return a.exec();
}
