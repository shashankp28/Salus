#include <Constants.h>
#include <AccessRule.h>
#include <HierarchyNode.h>

AccessRule::AccessRule(HierarchyNode *node, CompareType compareType, int distance)
{
    this->node = node;
    this->compareType = compareType;
    this->distance = distance;
}

CompareType AccessRule::getCompareType()
{
    return compareType;
}

HierarchyNode *AccessRule::getNode()
{
    return node;
}

int AccessRule::getDistance()
{
    return distance;
}

void AccessRule::setNode(HierarchyNode *node)
{
    this->node = node;
}

void AccessRule::setCompareType(CompareType compareType)
{
    this->compareType = compareType;
}

void AccessRule::setDistance(int distance)
{
    this->distance = distance;
}