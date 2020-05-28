#include "mytcpserver.h"
#include "mainwindow.h"
#include "mytcpserver.h"
#include "mytcpserver.h"
#include "qmessagebox.h"



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
    uiPTR->Network_status->setStyleSheet( "border-radius: 10px;"
                                           " background: green;"
                                             "color: green;"
                                            "height:24;"
                                            "width:24;"
                                          );
    uiPTR->statusLight_Power->setStyleSheet( "border-radius: 10px;"
                                           " background: green;"
                                             "color: green;"
                                            "height:24;"
                                            "width:24;"
                                          );

    robotSocket=server->nextPendingConnection();
    robotSocket->write("Welcome Client\r\n");
    robotSocket->flush();
    robotSocket->waitForBytesWritten(3000);
    connectionFlag=true;
    //socket->close();

}
void myTCPServer::sendMessage(QString message)
{
    if(robotSocket!=nullptr)
    {
       if(robotSocket->isOpen())
       {
            //Send the message
            QByteArray ba = message.toLocal8Bit();
            const char *send = ba.data();
            robotSocket->write(send);
            robotSocket->flush();

            //Look for a receive message
            QString receivedMessage=robotSocket->readAll();
            if(receivedMessage!=nullptr)
            {
            parseReceivedMessage(receivedMessage);
            receivedMessage ="Knight Guard: "+receivedMessage;
            uiPTR->commandTable->append(receivedMessage);
            }


       }
       if((robotSocket->state()!=QAbstractSocket::ConnectedState)&&connectionFlag==true)
       {

           uiPTR->Network_status->setStyleSheet( "border-radius: 10px;"
                                                  " background: red;"
                                                    "color: red;"
                                                   "height:24;"
                                                   "width:24;"
                                                 );
           QMessageBox msgBox;
           msgBox.setText("ERROR: ROBOT LOST CONNECTION");
           msgBox.exec();
           connectionFlag=false;
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
    //Fill in the connection info into the UI fields
    uiPTR->textInput_Network_Port->setText("8000");
    uiPTR->textInput_Network_Adress->setText(server->serverAddress().toString());

}

void myTCPServer:: parseReceivedMessage(QString message)
{
    /*
    if(message.startsWith("prox-"))
    {
        for (int i=0;i<message.count();i++)
           message[i]=message[i].split(",").first(); // replacing whole row with only first value
        uiPTR->proxBar_1->setValue()

    }
    */



}

