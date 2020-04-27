#ifndef SERIALCONNECTION_H
#define SERIALCONNECTION_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class SerialConnection
{
public:
    SerialConnection();
    QString comPort;
    int speed=0;


};

#endif // SERIALCONNECTION_H
