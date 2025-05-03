#include "car.h"

void Car::generateCarIssues()
{
    vector<string> carParts = {"Engine",
                               "Chassis / Suspension",
                               "Braking system",
                               "Steering system",
                               "Electrical system"};
    map<string, vector<pair<string, int>>> partsIssues = {
        {"Engine", {
                   {"Blown head gasket", 1200},
                   {"Worn timing belt", 600},
                   {"Leaking oil pump", 700},
                   {"Clogged fuel injector", 450},
                   {"Damaged turbocharger", 1500}
                   }},
        {"Chassis / Suspension", {
                                 {"Worn shock absorber", 500},
                                 {"Bent control arm", 400},
                                 {"Broken suspension spring", 450},
                                 {"Damaged stabilizer link", 300},
                                 {"Worn-out control arm bushing", 250}
                                 }},
        {"Braking system", {
                           {"Rusted brake disc", 350},
                           {"Worn-out brake pads", 200},
                           {"Cracked brake hose", 220},
                           {"Faulty brake master cylinder", 600},
                           {"Leaking brake wheel cylinder", 320}
                           }},
        {"Steering system", {
                            {"Leaking steering rack", 800},
                            {"Worn tie rod", 300},
                            {"Loose tie rod end", 280},
                            {"Damaged power steering pump", 650},
                            {"Cracked power steering fluid reservoir", 200}
                            }},
        {"Electrical system",   {
                                {"Faulty alternator", 700},
                                {"Dead battery", 400},
                                {"Broken starter motor", 500},
                                {"Burnt ignition module", 450},
                                {"Malfunctioning crankshaft position sensor", 350}
                                }}
    };

    random_device randDev;
    mt19937 gen(randDev());

    uniform_int_distribution<> issueCountDist(1, MAX_CAR_ISSUES);
    int issueCount = issueCountDist(gen);

    set<string> alreadyUsedIssues;

    while ((int)issues.size() < issueCount)
    {
        uniform_int_distribution<> carPartDist(0, carParts.size() - 1);
        string carPart = carParts[carPartDist(gen)];

        vector<pair<string, int>> issueList = partsIssues[carPart];

        uniform_int_distribution<> carIssueDist(0, issueList.size() - 1);
        pair<string, int> carIssue = issueList[carIssueDist(gen)];

        string issueKey = carPart + ":" + carIssue.first;

        if (alreadyUsedIssues.find(issueKey) == alreadyUsedIssues.end())
        {
            alreadyUsedIssues.insert(issueKey);
            issues[carIssue.first] = carIssue.second;
        }
    }
}

Car::Car()
{
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

    generateCarIssues();
}

Car::~Car() {
    qDebug().noquote() << "Car destroyed - " << registrationNumber;
}

void Car::printDebugInfo()
{
    qDebug().noquote() << brand << "\t" << model << "\t" << year << "\t"
         << color << "\t" << registrationNumber;
}

string Car::getCarInfo()
{
    ostringstream oss;
    oss << brand << " " << model << " " << year << "\n"
        << color << " " << registrationNumber;
    return oss.str();
}

map<string, int> Car::getIssues()
{
    return issues;
}


string Car::getCarRegistrationNumber()
{
    return registrationNumber;
}
