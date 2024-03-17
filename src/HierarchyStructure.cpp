#include <HierarchyNode.h>
#include <HierarchyStructure.h>


HierarchyStructure::HierarchyStructure(std::string name)
{
    this->name = name;
}

std::string HierarchyStructure::getName()
{
    return name;
}

HierarchyNode *HierarchyStructure::getRoot()
{
    return root;
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

HierarchyNode *HierarchyStructure::getMember(std::string name)
{
    return members[name];
}
