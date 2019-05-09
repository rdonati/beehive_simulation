#include "mainwindow.h"
#include "weatherwidg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WeatherWidg ww;
    ww.show();
    /*
    MainWindow w;
    w.show();
    */

    return a.exec();
}
