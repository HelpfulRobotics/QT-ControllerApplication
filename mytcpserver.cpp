#include "mytcpserver.h"
#include "mainwindow.h"
#include "mytcpserver.h"
#include "mytcpserver.h"



myTCPServer::myTCPServer()
{


    server = new QTcpServer(this);

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

    if(!server->listen(QHostAddress::AnyIPv4,8000))
    {
        qDebug()<<"Server could not start";

    }
    else
    {

        qDebug()<<"Server started";
    }
}

void myTCPServer::newConnection()
{
    //uiPTR->Network_status->setStyleSheet("{color:#15b318}");

    robotSocket=server->nextPendingConnection();
    robotSocket->write("Welcome Client\r\n");
    robotSocket->flush();
    robotSocket->waitForBytesWritten(3000);
    robotSocket->write("This is quinton\r\n");
    robotSocket->flush();
    //robotSocket->waitForBytesWritten(3000);
    //socket->close();

}
void myTCPServer::sendMessage(QString message)
{
    if(robotSocket!=nullptr)
    {
       if(robotSocket->isOpen())
       {
            //robotSocket->write(message);
            QByteArray ba = message.toLocal8Bit();
            const char *send = ba.data();
            robotSocket->write(send);
            robotSocket->flush();
       }
    }
}

void myTCPServer::closeConnection()
{
    robotSocket->close();
}

void myTCPServer::getUI(Ui::MainWindow *ui)
{
    uiPTR=ui;
}

