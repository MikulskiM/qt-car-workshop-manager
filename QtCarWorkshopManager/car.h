#ifndef CAR_H
#define CAR_H

#include <string>
#include <map>
#include <random>
#include <vector>
#include <QDebug>
#include <sstream>

#define MAX_CAR_ISSUES 5

using namespace std;

class Car
{
    string brand;
    string model;
    string color;
    int year;
    string registrationNumber;
    map<string, int> issues;

    void generateCarIssues();

public:
    Car();
    ~Car();

    void printDebugInfo();
    string getCarInfo();
    map<string, int> getIssues();
    void clearIssues();
    string getCarRegistrationNumber();
};

#endif // CAR_H
