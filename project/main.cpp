#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginDialog logdia;
    logdia.exec();
    if(!logdia.canLog())
    {
        return 0;
    }
    MainWindow w(nullptr,logdia.name);
    w.name=logdia.name;
    w.show();
    return a.exec();
}
