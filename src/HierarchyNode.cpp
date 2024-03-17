#include <HierarchyNode.h>
#include <HierarchyStructure.h>
#include <unordered_map>
#include <string>
#include <iostream>

HierarchyNode::HierarchyNode(std::string name, HierarchyStructure *structure, HierarchyNode *parent)
{
    this->name = name;
    this->structure = structure;
    this->parents = new std::unordered_map<std::string, HierarchyNode *>();
    this->children = new std::unordered_map<std::string, HierarchyNode *>();
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
    return parents;
}

std::unordered_map<std::string, HierarchyNode *> *HierarchyNode::getChildren()
{
    return children;
}

void HierarchyNode::addParent(HierarchyNode *parent)
{
    if (parent != nullptr)
    {
        parents->insert(std::pair<std::string, HierarchyNode *>(parent->getName(), parent));
    }
}

void HierarchyNode::addChild(HierarchyNode *child)
{
    if (child != nullptr)
    {
        children->insert(std::pair<std::string, HierarchyNode *>(child->getName(), child));
    }
}

void HierarchyNode::removeParent(HierarchyNode *parent)
{
    if (parent != nullptr)
    {
        parents->erase(parent->getName());
    }
}

void HierarchyNode::removeChild(HierarchyNode *child)
{
    if (child != nullptr)
    {
        children->erase(child->getName());
    }
}
