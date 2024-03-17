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

void SalusEngine::addHierarchy(HierarchyStructure *hierarchy)
{
    if (hierarchy != nullptr)
    {
        hierarchies[hierarchy->getName()] = hierarchy;
    }
}

void SalusEngine::removeHierarchy(std::string name)
{
    hierarchies.erase(name);
}

HierarchyStructure *SalusEngine::getHierarchy(std::string name)
{
    return hierarchies[name];
}
