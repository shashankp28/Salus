#include <HierarchyNode.h>
#include <HierarchyStructure.h>
#include <unordered_map>
#include <string>

HierarchyNode::HierarchyNode(std::string name, HierarchyStructure *structure, HierarchyNode *parent)
{
    this->name = name;
    this->structure = structure;
    this->addParent(parent);
}

std::string HierarchyNode::getName()
{
    return name;
}

HierarchyStructure *HierarchyNode::getStructure()
{
    return structure;
}

std::unordered_map<std::string, HierarchyNode *> *HierarchyNode::getParents()
{
    return &parents;
}

std::unordered_map<std::string, HierarchyNode *> *HierarchyNode::getChildren()
{
    return &children;
}
