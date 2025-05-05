#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

using namespace std;

class TcpServer : public QObject
{
    Q_OBJECT

public:
    TcpServer();
    void start();

private:
    QTcpServer* server;
    QTcpSocket* socket;

private slots:
    void newConnection();
    void readData();

};

#endif // TCPSERVER_H
