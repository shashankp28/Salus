#include <iostream>
#include <Constants.h>
#include <AccessRule.h>
#include <HierarchyNode.h>
#include <HierarchyStructure.h>
#include <queue>

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

bool AccessRule::canAccess(HierarchyNode *criterion)
{
    HierarchyStructure *targetStructure = node->getStructure();
    HierarchyStructure *currentStructure = criterion->getStructure();
    if (targetStructure != currentStructure)
    {
        return false;
    }
    std::cout << node->getName() << " " << criterion->getName() << std::endl;
    if (node == criterion)
    {
        switch (compareType)
        {
        case CompareType::EQUAL:
        case CompareType::LESS_EQUAL:
        case CompareType::GREATER_EQUAL:
            return true;
        default:
            return false;
        }
    }
    if (compareType == CompareType::EQUAL)
    {
        return false;
    }
    HierarchyNode *start, *goal;
    if (compareType == CompareType::GREATER || compareType == CompareType::GREATER_EQUAL)
    {
        start = criterion;
        goal = node;
    }
    else
    {
        start = node;
        goal = criterion;
    }
    int distance = 0;
    std::queue<std::pair<HierarchyNode *, int>> q;
    q.push({start, 0});
    while (!q.empty())
    {
        HierarchyNode *current = q.front().first;
        int currentDistance = q.front().second;
        q.pop();
        std::unordered_map<std::string, HierarchyNode *> *children = current->getChildren();
        for (auto const &entry : *children)
        {
            HierarchyNode *child = entry.second;
            if (child == goal)
            {
                distance = currentDistance + 1;
                break;
            }
            q.push({child, currentDistance + 1});
        }
        if (distance != 0)
        {
            break;
        }
    }
    std::cout << "Disatnce Measured: " << distance << "Target Distance: " << this->distance << std::endl;
    if (distance == 0)
    {
        return compareType == CompareType::NOT_EQUAL;
    }
    return distance <= this->distance;
}

std::string AccessRule::toString()
{
    std::string compareTypeStr;
    switch (compareType)
    {
    case CompareType::EQUAL:
        compareTypeStr = "EQUAL";
        break;
    case CompareType::NOT_EQUAL:
        compareTypeStr = "NOT_EQUAL";
        break;
    case CompareType::GREATER:
        compareTypeStr = "GREATER";
        break;
    case CompareType::LESS:
        compareTypeStr = "LESS";
        break;
    case CompareType::GREATER_EQUAL:
        compareTypeStr = "GREATER_EQUAL";
        break;
    case CompareType::LESS_EQUAL:
        compareTypeStr = "LESS_EQUAL";
        break;
    }
    std::string result = "{\n";
    result += "\t'compare_type': '" + compareTypeStr + "',\n";
    result += "\t'node': '" + node->getName() + "',\n";
    result += "\t'distance': " + std::to_string(distance) + "'\n";
    return result + "\n}";
}
