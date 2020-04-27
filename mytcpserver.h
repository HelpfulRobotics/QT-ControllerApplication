#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class myTCPServer : public QObject
{
    Q_OBJECT
public:
    explicit myTCPServer(QObject *parent = nullptr);

    void closeConnection();
signals:

public slots:

    void newConnection();
    void sendMessage(QString message);

private:
    QTcpServer *server;
    QTcpSocket *robotSocket;
};

#endif // MYTCPSERVER_H
