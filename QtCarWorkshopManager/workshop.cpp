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
