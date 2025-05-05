#include "workshop.h"

Workshop::Workshop() : takings(0)
{
    generateWorkshopAddress();
}

void Workshop::generateWorkshopAddress()
{
    vector<string> cities = {"Gdansk", "Warsaw", "Krakow", "Katowice", "Wroclaw"};
    vector<string> roads = {"Ogrodowa", "Szeroka", "Kolorowa", "Mechaniczna", "Dziurawa"};

    random_device rd;
    mt19937 gen(rd());

    city = cities[uniform_int_distribution<>(0, cities.size() - 1)(gen)];
    string road = roads[uniform_int_distribution<>(0, roads.size() - 1)(gen)];
    int number = uniform_int_distribution<>(1, 299)(gen);

    address = road + " " + to_string(number);

    qDebug().noquote() << "Workshop created - " << city << " " << address;
}


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
    string data = "city=" + city + "\n";
    data += "address=" + address + "\n";
    data += "takings=" + to_string(takings) + "\n";

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
