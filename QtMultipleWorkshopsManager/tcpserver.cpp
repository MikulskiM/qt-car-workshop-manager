#include "tcpserver.h"

TcpServer::TcpServer()
{
    server = new QTcpServer();
    connect(server, &QTcpServer::newConnection, this, &TcpServer::newConnection);
}

void TcpServer::start()
{
    if (server->listen(QHostAddress::Any, 12345)) {
        qDebug() << "TCP server started on port 12345";
    } else {
        qDebug() << "Server failed to start:" << server->errorString();
    }
}

void TcpServer::newConnection()
{
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &TcpServer::readData);
    qDebug() << "Client connected from" << socket->peerAddress().toString();
}

void TcpServer::readData()
{
    QByteArray data = socket->readAll();
    qDebug().noquote() << "Data read:";
    qDebug().noquote() << data;
}
