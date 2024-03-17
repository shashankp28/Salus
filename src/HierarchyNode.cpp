#include <HierarchyNode.h>
#include <HierarchyStructure.h>
#include <unordered_map>
#include <string>

HierarchyNode::HierarchyNode(std::string name, HierarchyNode *parent)
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

// TODO : Change here
void HierarchyNode::addParent(HierarchyNode *parent)
{
    if (parent != nullptr)
    {
        parents[parent->getName()] = parent;
        parent->addChild(this);
    }
}

void HierarchyNode::addChild(HierarchyNode *child)
{
    if (child != nullptr)
    {
        children[child->getName()] = child;
    }
}

void HierarchyNode::removeParent(HierarchyNode *parent)
{
    if (parent != nullptr)
    {
        parents.erase(parent->getName());
        parent->removeChild(this);
    }
}

void HierarchyNode::removeChild(HierarchyNode *child)
{
    if (child != nullptr)
    {
        children.erase(child->getName());
    }
}
