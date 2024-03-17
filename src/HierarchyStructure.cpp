#include <HierarchyNode.h>
#include <HierarchyStructure.h>

HierarchyStructure::HierarchyStructure(std::string name, HierarchyNode *root)
{
    this->name = name;
    this->setRoot(root);
    this->addMember(root);
}

std::string HierarchyStructure::getName()
{
    return name;
}

HierarchyNode *HierarchyStructure::getRoot()
{
    return root;
}

HierarchyNode *HierarchyStructure::getMember(std::string name)
{
    if (members.find(name) == members.end())
    {
        return nullptr;
    }
    return members[name];
}

std::unordered_map<std::string, HierarchyNode *> *HierarchyStructure::getMembers()
{
    return &members;
}

void HierarchyStructure::setRoot(HierarchyNode *root)
{
    this->root = root;
}

void HierarchyStructure::addMember(HierarchyNode *member)
{
    if (member != nullptr)
    {
        members[member->getName()] = member;
    }
}

void HierarchyStructure::removeMember(HierarchyNode *member)
{
    if (member != nullptr)
    {
        members.erase(member->getName());
    }
}

void HierarchyStructure::removeMember(std::string name)
{
    if (members.find(name) != members.end())
    {
        members.erase(name);
    }
}