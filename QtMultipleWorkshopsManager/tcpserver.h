#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

using namespace std;

class MainWindow; // forward declaration so readData() can use mainwindow->handleNewWorkshop(takings, issues)

class TcpServer : public QObject
{
    Q_OBJECT

public:
    TcpServer(MainWindow* mw);
    void start();

private:
    QTcpServer* server;
    QTcpSocket* socket;
    MainWindow* mainWindow;

    void handleNewConnection();
    void readData();
};

#endif // TCPSERVER_H
