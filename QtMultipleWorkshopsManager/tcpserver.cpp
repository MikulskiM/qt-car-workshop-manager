#include "tcpserver.h"
#include "mainwindow.h"

TcpServer::TcpServer(MainWindow* mw)
{
    server = new QTcpServer(this);
    mainWindow = mw;

    connect(server, &QTcpServer::newConnection, this, [=]() {
        handleNewConnection();
    });
}

void TcpServer::start()
{
    if (server->listen(QHostAddress::Any, 12345)) {
        qDebug() << "TCP server started on port 12345";
    } else {
        qDebug() << "Server failed to start:" << server->errorString();
    }
}

void TcpServer::handleNewConnection()
{
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, [=]() {
        readData();
    });
    qDebug() << "Client connected from" << socket->peerAddress().toString();
}

void TcpServer::readData()
{
    QByteArray raw = socket->readAll();
    QList<QByteArray> lines = raw.split('\n');

    QString city;
    QString address;
    int takings = 0;
    QMap<QString, int> issues;

    for (QByteArray line : lines) {
        if (line.startsWith("city=")) {
            city = line.mid(5).trimmed();
        } else if (line.startsWith("address=")) {
            address = line.mid(8).trimmed();
        } else if (line.startsWith("takings=")) {
            takings = line.mid(8).toInt();
        } else if (line.startsWith("issue=")) {
            QList<QByteArray> parts = line.mid(6).split(':');
            if (parts.size() == 2) {
                issues[QString(parts[0])] += parts[1].toInt();
            }
        }
    }

    mainWindow->handleNewWorkshop(city, address, takings, issues);
}

