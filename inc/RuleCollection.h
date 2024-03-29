#ifndef RULECOLLECTION_H
#define RULECOLLECTION_H

#include <AccessRule.h>
#include <HierarchyNode.h>
#include <vector>
#include <string>

class RuleCollection
{
private:
    std::string name;
    std::vector<AccessRule *> *rules;

public:
    RuleCollection(std::string name);
    std::string getName();
    std::vector<AccessRule *> *getRules();
    void addRule(AccessRule *rule);
    void removeRule(AccessRule *rule);
    void removeRule(int index);
    bool canAccess(HierarchyNode *criterion);
    std::string toString();
};

#endif