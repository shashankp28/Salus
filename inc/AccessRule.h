#ifndef ACCESSRULE_H
#define ACCESSRULE_H

#include <HierarchyNode.h>
#include <Constants.h>

class AccessRule
{
private:
    CompareType compareType;
    HierarchyNode *node;
    int distance;

public:
    AccessRule(HierarchyNode *node, CompareType compareType, int distance);
    CompareType getCompareType();
    HierarchyNode *getNode();
    int getDistance();
    void setNode(HierarchyNode *node);
    void setCompareType(CompareType compareType);
    void setDistance(int distance);
    ~AccessRule();
};

#endif