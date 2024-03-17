#ifndef SALUSENGINE_H
#define SALUSENGINE_H

#include <PieceOfInformation.h>
#include <unordered_map>
#include <RuleCollection.h>
#include <HierarchyStructure.h>

class SalusEngine
{
private:
    std::unordered_map<std::string, PieceOfInformation *> *informationBank;
    std::unordered_map<std::string, RuleCollection *> *ruleCollections;
    std::unordered_map<std::string, HierarchyStructure *> *hierarchies;

public:
    SalusEngine(std::string topUser);
    // Piece Of Information Area
    void addPieceOfInformation(std::string id, std::string owner,
                               std::vector<std::string> readAccessList,
                               std::vector<std::string> writeAccessList);
    void removePieceOfInformation(std::string id);
    void changePieceOfInformationOwner(std::string id, std::string newOwner);
    // Access Control List Area
    void addRuleToReaadAccessList(std::string id, std::string newRuleCollection);
    void removeRuleFromReadAccessList(std::string id, std::string ruleCollection);
    void addRuleToWriteAccessList(std::string id, std::string newRuleCollection);
    void removeRuleFromWriteAccessList(std::string id, std::string ruleCollection);
    // Hierarchy Area
    void addNewHierarchyStructure(std::string name, std::string root);
    void addNewCriterionForHierarchy(std::string hierarchyName, std::string criterionName,
                                     std::string parentCriterion);
    void removeCriterionFromHierarchy(std::string hierarchyName, std::string criterionName);
    void renameCriterionFromHierarchy(std::string hierarchyName, std::string criterionName,
                                      std::string newCriterionName);
    void changeCriterionParent(std::string hierarchyName, std::string criterionName,
                               std::string newParent);
    void removeHierarchy(std::string name);
    // Rule Collection Area
    void addNewRuleCollection(std::string name);
    void removeRuleCollection(std::string name);
    void appendRuleToCollection(std::string collectionName, std::string hierarchyName,
                                std::string criterionName, std::string compareType,
                                int distacne);
    void removeRuleFromCollection(std::string collectionName, int index);
};
#endif