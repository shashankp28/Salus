#ifndef HIERARCHYNODE_H
#define HIERARCHYNODE_H

#include <string>
#include <unordered_map>
#include <HierarchyStructure.h>

class HierarchyNode
{
private:
    std::string name;
    std::unordered_map<std::string, HierarchyNode *> parents;
    HierarchyStructure *structure;
    std::unordered_map<std::string, HierarchyNode *> children;

public:
    HierarchyNode(std::string name, HierarchyStructure *structure, HierarchyNode *parent);
    std::string getName();
    HierarchyStructure *getStructure();
    std::unordered_map<std::string, HierarchyNode *> *getParents();
    std::unordered_map<std::string, HierarchyNode *> *getChildren();
    void addParent(HierarchyNode *parent);
    void addChild(HierarchyNode *child);
    void removeParent(HierarchyNode *parent);
    void removeChild(HierarchyNode *child);
};

#endif