#include <RuleCollection.h>
#include <vector>

RuleCollection::RuleCollection(std::string name)
{
    this->name = name;
    rules = new std::vector<AccessRule *>();
}

std::string RuleCollection::getName()
{
    return name;
}

std::vector<AccessRule *> *RuleCollection::getRules()
{
    return rules;
}

void RuleCollection::addRule(AccessRule *rule)
{
    if (rule != nullptr)
    {
        rules->push_back(rule);
    }
}

void RuleCollection::removeRule(AccessRule *rule)
{
    if (rule != nullptr)
    {
        for (int i = 0; i < (int)rules->size(); i++)
        {
            if (rules->at(i) == rule)
            {
                rules->erase(rules->begin() + i);
                break;
            }
        }
    }
}

void RuleCollection::removeRule(int index)
{
    if (index >= 0 && index < (int)rules->size())
    {
        rules->erase(rules->begin() + index);
    }
}

bool RuleCollection::canAccess(HierarchyNode *criterion)
{
    bool accessGranted = true;
    for (int i = 0; i < (int)rules->size(); i++)
    {
        AccessRule *rule = rules->at(i);
        accessGranted = accessGranted && rule->canAccess(criterion);
    }
    return accessGranted;
}
