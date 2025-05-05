#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <string>
#include <random>
#include <vector>
#include <QDebug>
#include <QTcpSocket>

using namespace std;

class Workshop
{
    string city;
    string address;
    int takings;
    map<string, int> issues;

public:
    Workshop();
    void generateWorkshopAddress();

    void addTakings(int amount);
    void addIssue(string issue, int cost);

    string serializeData();
    void sendData(string host = "127.0.0.1", int port = 12345);
};

#endif // WORKSHOP_H
