#ifndef PIECEOFINFORMATION_H
#define PIECEOFINFORMATION_H

#include <HierarchyNode.h>
#include <AccessRule.h>
#include <RuleCollection.h>
#include <string>
#include <ctime>
#include <unordered_map>

class PieceOfInformation
{

private:
    std::string id;
    HierarchyNode *owner;
    std::time_t creationTime;
    HierarchyNode *lastModifiedBy;
    std::time_t lastModifiedTime;
    std::unordered_map<std::string, RuleCollection *> readAccessList;
    std::unordered_map<std::string, RuleCollection *> writeAccessList;

public:
    PieceOfInformation(std::string id, HierarchyNode *owner);
    std::string getId();
    HierarchyNode *getOwner();
    std::time_t getCreationTime();
    HierarchyNode *getLastModifiedBy();
    std::time_t getLastModifiedTime();
    std::unordered_map<std::string, RuleCollection *> *getReadAccessList();
    std::unordered_map<std::string, RuleCollection *> *getWriteAccessList();
    void setOwner(HierarchyNode *owner);
    void setLastModifiedBy(HierarchyNode *lastModifiedBy);
    void setLastModifiedTime(std::time_t lastModifiedTime);
    void addReadAccessRule(std::string userId, RuleCollection *ruleCollection);
    void addWriteAccessRule(std::string userId, RuleCollection *ruleCollection);
    void removeReadAccessRule(std::string userId);
    void removeWriteAccessRule(std::string userId);
};

#endif