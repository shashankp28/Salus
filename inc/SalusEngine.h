#ifndef SALUSENGINE_H
#define SALUSENGINE_H

#include <PieceOfInformation.h>
#include <unordered_map>
#include <RuleCollection.h>
#include <HierarchyStructure.h>

class SalusEngine
{
private:
    std::unordered_map<std::string, PieceOfInformation *> informationBank;
    std::unordered_map<std::string, RuleCollection *> ruleCollections;
    std::unordered_map<std::string, HierarchyStructure *> hierarchies;
};
#endif