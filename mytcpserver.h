#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <ui_mainwindow.h>

class myTCPServer : public QObject
{
    Q_OBJECT
public:
    explicit myTCPServer();
    void getUI(Ui::MainWindow* ui);

    void closeConnection();
signals:

public slots:

    void newConnection();
    void sendMessage(QString message);


private:
    QTcpServer *server;
    QTcpSocket *robotSocket=nullptr;
    Ui::MainWindow* uiPTR;
    bool connectionFlag=false;
    void parseReceivedMessage(QString message);
};

#endif // MYTCPSERVER_H
