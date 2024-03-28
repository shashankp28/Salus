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
    void addCollectionToReadAccessList(std::string id, std::string ruleCollectionName);
    void removeCollectionFromReadAccessList(std::string id, std::string ruleCollectionName);
    void addCollectionToWriteAccessList(std::string id, std::string ruleCollectionName);
    void removeCollectionFromWriteAccessList(std::string id, std::string ruleCollectionName);
    // Hierarchy Area
    void addNewHierarchyStructure(std::string name, std::string root);
    void addNewCriterionForHierarchy(std::string hierarchyName, std::string criterionName,
                                     std::vector<std::string> parentCriterion);
    void removeCriterionFromHierarchy(std::string hierarchyName, std::string criterionName);
    void renameCriterionFromHierarchy(std::string hierarchyName, std::string criterionName,
                                      std::string newCriterionName);
    void changeCriterionParents(std::string hierarchyName, std::string criterionName,
                                std::vector<std::string> newParents);
    void removeHierarchy(std::string name);
    // Rule Collection Area
    void addNewRuleCollection(std::string name);
    void appendRuleToCollection(std::string collectionName, std::string hierarchyName,
                                std::string criterionName, std::string compareType,
                                int distacne);
    void removeRuleFromCollection(std::string collectionName, int index);
    void removeRuleCollection(std::string name);
    // Access Checker
    bool canRead(std::string hierarchyName, std::string criterionName, std::string id);
    bool canWrite(std::string username, std::string hierarchyName,
                  std::string criterionName, std::string id);
    // Engine Metadata Reader
    std::string getPieceOfInformation(std::string id);
    std::string getRuleCollection(std::string name);
    std::string getHierarchyStructure(std::string name);
    std::vector<std::string> showAllHierarchies();
    std::vector<std::string> showAllRuleCollections();
    // Waiting shutdown
    void shutdown(std::string messages);
};
#endif