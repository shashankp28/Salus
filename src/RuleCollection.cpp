/*
#ifndef RULECOLLECTION_H
#define RULECOLLECTION_H

#include <AccessRule.h>
#include <vector>
#include <string>

class RuleCollection
{
private:
    std::string name;
    std::vector<AccessRule *> rules;

public:
    RuleCollection(std::string name);
    std::string getName();
    std::vector<AccessRule *> *getRules();
    void addRule(AccessRule *rule);
    void removeRule(AccessRule *rule);
    void removeRule(int index);
};

#endif
*/

#include <RuleCollection.h>

RuleCollection::RuleCollection(std::string name)
{
    this->name = name;
}

std::string RuleCollection::getName()
{
    return name;
}

std::vector<AccessRule *> *RuleCollection::getRules()
{
    return &rules;
}

void RuleCollection::addRule(AccessRule *rule)
{
    if (rule != nullptr)
    {
        rules.push_back(rule);
    }
}

void RuleCollection::removeRule(AccessRule *rule)
{
    if (rule != nullptr)
    {
        for (int i = 0; i < (int)rules.size(); i++)
        {
            if (rules[i] == rule)
            {
                rules.erase(rules.begin() + i);
                break;
            }
        }
    }
}

void RuleCollection::removeRule(int index)
{
    if (index >= 0 && index < (int)rules.size())
    {
        rules.erase(rules.begin() + index);
    }
}
