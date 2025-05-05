#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <string>
#include <random>
#include <vector>
#include <QDebug>
#include <map>

using namespace std;

class Workshop
{
    string city;
    string address;
    int takings;
    map<string, int> issues;

public:
    Workshop();
    ~Workshop();

    void generateWorkshopAddress();

    int getTakings();
    void addTakings(int newTakings);

    map<string, int> getIssues();
    void addIssue(string name, int cost);

    void mergeIssues(QMap<QString, int> newIssues);

    void setCity(string c);
    void setAddress(string a);
    string getCity();
    string getAddress();
};

#endif // WORKSHOP_H
