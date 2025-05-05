#include "workshop.h"

Workshop::Workshop() : city("undefined"), address("undefined"), takings(0) {}

void Workshop::addTakings(int amount)
{
    takings += amount;
}

void Workshop::addIssue(string issue, int cost)
{
    issues[issue] += cost;
}

string Workshop::serializeData()
{
    string data = "takings=" + to_string(takings) + "\n";
    for (auto& issue : issues) {
        data += "issue=" + issue.first + ":" + to_string(issue.second) + "\n";
    }
    return data;
}

void Workshop::sendData(string host, int port)
{
    QTcpSocket socket;

    qDebug().noquote() << "\nSending data:\n" << serializeData();

    socket.connectToHost(QString::fromStdString(host), port);
    if (socket.waitForConnected()) {
        string data = serializeData();
        socket.write(QByteArray::fromStdString(data));
        socket.flush();
        socket.waitForBytesWritten();
        socket.disconnectFromHost();
    }

    qDebug().noquote() << "Data sent successfully!";
}
