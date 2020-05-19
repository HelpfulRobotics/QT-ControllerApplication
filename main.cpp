#include "mainwindow.h"
#include "mytcpserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    //myTCP.sendMessage("this is quinton");
    return a.exec();
}
