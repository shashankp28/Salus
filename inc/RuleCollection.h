#ifndef RULECOLLECTION_H
#define RULECOLLECTION_H

#include <AccessRule.h>
#include <vector>
#include <string>

class RuleCollection
{
private:
    std::string name;
    std::vector<AccessRule*> rules;
};

#endif