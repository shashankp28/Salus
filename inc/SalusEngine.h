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

public:
    SalusEngine();
    void addPieceOfInformation(PieceOfInformation *pieceOfInformation);
    void removePieceOfInformation(std::string id);
    PieceOfInformation *getPieceOfInformation(std::string id);
    void addRuleCollection(RuleCollection *ruleCollection);
    void removeRuleCollection(std::string name);
    RuleCollection *getRuleCollection(std::string name);
    // void addHierarchy(HierarchyStructure *hierarchy);
    void removeHierarchy(std::string name);
    HierarchyStructure *getHierarchy(std::string name);
};
#endif