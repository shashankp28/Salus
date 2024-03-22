#include <HierarchyNode.h>
#include <HierarchyStructure.h>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

HierarchyNode::HierarchyNode(std::string name, HierarchyStructure *structure,
                             std::vector<HierarchyNode *> *parents)
{
    this->name = name;
    this->structure = structure;
    this->parents = new std::unordered_map<std::string, HierarchyNode *>();
    this->addParents(parents);
    this->children = new std::unordered_map<std::string, HierarchyNode *>();
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

void HierarchyNode::setName(std::string newName)
{
    name = newName;
}

void HierarchyNode::addParent(HierarchyNode *parent)
{
    if (parent != nullptr)
    {
        parents->insert(std::pair<std::string, HierarchyNode *>(parent->getName(), parent));
    }
}

void HierarchyNode::addParents(std::vector<HierarchyNode *> *parents)
{
    if (parents != nullptr)
    {
        for (auto it = parents->begin(); it != parents->end(); it++)
        {
            (*it)->addChild(this);
            this->addParent(*it);
        }
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

void HierarchyNode::removeParents(std::vector<HierarchyNode *> *parents)
{
    if (parents != nullptr)
    {
        for (auto it = parents->begin(); it != parents->end(); it++)
        {
            (*it)->removeChild(this);
            this->removeParent(*it);
        }
    }
}

void HierarchyNode::removeChild(HierarchyNode *child)
{
    if (child != nullptr)
    {
        children->erase(child->getName());
    }
}

std::string HierarchyNode::toString()
{
    std::string result = "HierarchyNode: " + name + "\n";
    result += "Parents: ";
    for (auto it = parents->begin(); it != parents->end(); it++)
    {
        result += it->first + " ";
    }
    result += "\nChildren: ";
    for (auto it = children->begin(); it != children->end(); it++)
    {
        result += it->first + " ";
    }
    result += "\n";
    return result;
}