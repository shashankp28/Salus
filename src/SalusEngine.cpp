/*
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
    void addHierarchy(HierarchyStructure *hierarchy);
    void removeHierarchy(std::string name);
    HierarchyStructure *getHierarchy(std::string name);
};
#endif
*/

#include <SalusEngine.h>

SalusEngine::SalusEngine()
{
}

void SalusEngine::addPieceOfInformation(PieceOfInformation *pieceOfInformation)
{
    if (pieceOfInformation != nullptr)
    {
        informationBank[pieceOfInformation->getId()] = pieceOfInformation;
    }
}

void SalusEngine::removePieceOfInformation(std::string id)
{
    informationBank.erase(id);
}

PieceOfInformation *SalusEngine::getPieceOfInformation(std::string id)
{
    return informationBank[id];
}

void SalusEngine::addRuleCollection(RuleCollection *ruleCollection)
{
    if (ruleCollection != nullptr)
    {
        ruleCollections[ruleCollection->getName()] = ruleCollection;
    }
}

void SalusEngine::removeRuleCollection(std::string name)
{
    ruleCollections.erase(name);
}

RuleCollection *SalusEngine::getRuleCollection(std::string name)
{
    return ruleCollections[name];
}

// void SalusEngine::addHierarchy(HierarchyStructure *hierarchy)
// {
//     if (hierarchy != nullptr)
//     {
//         hierarchies[hierarchy->getName()] = hierarchy;
//     }
// }

void SalusEngine::removeHierarchy(std::string name)
{
    hierarchies.erase(name);
}

HierarchyStructure *SalusEngine::getHierarchy(std::string name)
{
    return hierarchies[name];
}

// Path: src/main.cpp
