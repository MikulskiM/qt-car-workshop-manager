#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <string>
#include <random>
#include <vector>
#include <QDebug>

using namespace std;

class Workshop
{
    string city;
    string address;
    int takings;
    map<string, int> issues;

public:
    Workshop();

    void addTakings(int amount);
    void addIssue(string issue, int cost);
};

#endif // WORKSHOP_H
