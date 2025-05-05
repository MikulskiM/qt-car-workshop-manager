#include "workshop.h"

Workshop::Workshop()
{
    generateWorkshopAddress();
}

Workshop::~Workshop()
{
    qDebug().noquote() << "Workshop destroyed - " << city << " " << address;
}

void Workshop::generateWorkshopAddress()
{
    vector<string> cities = {"Gdansk", "Warsaw", "Krakow", "Katowice", "Wroclaw"};
    vector<string> roads = {"Ogrodowa", "Szeroka", "Kolorowa", "Mechaniczna", "Dziurawa"};

    random_device randDev;
    mt19937 gen(randDev());

    uniform_int_distribution<> cityDist(0, cities.size() - 1);
    city = cities[cityDist(gen)];

    uniform_int_distribution<> roadDist(0, roads.size() - 1);
    string road = roads[roadDist(gen)];

    uniform_int_distribution<> numberDist(0, 299);
    int number = numberDist(gen);

    address = road + to_string(number);

    qDebug().noquote() << "Workshop created - " << city << " " << address;
}

int Workshop::getTakings()
{
    return takings;
}

void Workshop::addTakings(int newTakings)
{
    takings = newTakings;
}

map<string, int> Workshop::getIssues()
{
    return issues;
}

void Workshop::addIssue(string name, int cost)
{
    issues[name] += cost;
}

string Workshop::getCity() {
    return city;
}

string Workshop::getAddress() {
    return address;
}

void Workshop::mergeIssues(QMap<QString, int> newIssues)
{
    for (auto issue = newIssues.begin(); issue != newIssues.end(); issue++) {
        issues[issue.key().toStdString()] += issue.value();
        takings += issue.value();
    }
}

void Workshop::setCity(string c)
{
    city = c;
}
void Workshop::setAddress(string a)
{
    address = a;
}
