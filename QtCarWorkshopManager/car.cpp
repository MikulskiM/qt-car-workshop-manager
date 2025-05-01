#include "car.h"

Car::Car() {
    vector<string> brands = {"Skoda", "Toyota", "Ford", "Volkswagen", "Opel"};
    map<string, vector<string>> models = {
        { "Skoda",      {"Octavia", "Fabia",    "Superb"} },
        { "Toyota",     {"Corolla", "Yaris",    "Avensis"} },
        { "Ford",       {"Focus",   "Fiesta",   "Mondeo"} },
        { "Volkswagen", {"Golf",    "Passat",   "Polo"} },
        { "Opel",       {"Astra",   "Insignia", "Corsa"} }
    };
    vector<string> colors = {"blue", "red", "black", "silver", "white"};
    vector<string> cities = {"GD", "KR", "PO", "WA", "NO"};

    random_device randDev;
    mt19937 gen(randDev());

    uniform_int_distribution<> brandDist(0, brands.size() - 1);
    brand = brands[brandDist(gen)];

    uniform_int_distribution<> colorDist(0, colors.size() - 1);
    color = colors[colorDist(gen)];

    // possible optimization for the future (don't generate more randoms)
    model = models.at(brand)[(brandDist(gen) + colorDist(gen)) % 3];

    uniform_int_distribution<> yearDist(2005, 2024);
    year = yearDist(gen);

    uniform_int_distribution<> cityDist(0, cities.size() - 1);
    std::uniform_int_distribution<> numDist(1000, 9999);
    registrationNumber = cities[cityDist(gen)] + " " + std::to_string(numDist(gen));

    issues = {};

    printInfo();
}

void Car::printInfo()
{
    qDebug() << brand << "\t" << model << "\t" << year << "\t"
         << color << "\t" << registrationNumber << "\n";
}
