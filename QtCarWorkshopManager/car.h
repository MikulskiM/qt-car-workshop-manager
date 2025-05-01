#ifndef CAR_H
#define CAR_H

#include <string>
#include <map>
#include <random>
#include <vector>
#include <QDebug>

using namespace std;

class Car
{
    string brand;
    string model;
    string color;
    int year;
    string registrationNumber;
    map<string, int> issues;

public:
    Car();

    void printInfo();
};

#endif // CAR_H
