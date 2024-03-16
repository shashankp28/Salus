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
};

#endif