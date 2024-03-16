#ifndef HIERARCHYNODE_H
#define HIERARCHYNODE_H

#include <string>
#include <unordered_map>
#include <HierarchyStructure.h>

class HierarchyNode
{
private:
    std::string name;
    HierarchyNode *parent;
    HierarchyStructure *structure;
    std::unordered_map<std::string, HierarchyNode *> children;
};

#endif