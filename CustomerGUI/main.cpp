#include "mainwindow.h"
#include "beechimes.h"
#include "welcomescreen.h"
#include <QApplication>
#include "fstream"

int main(int argc, char *argv[])
{
    std::fstream file;
    file.open("test.txt");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    WelcomeScreen ws;
    ws.show();
    /*BeeChimes bc;
    bc.show();*/

    return a.exec();
}
