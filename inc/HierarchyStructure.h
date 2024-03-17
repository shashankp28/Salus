#ifndef HIERRARCHYSTRUCTURE_H
#define HIERRARCHYSTRUCTURE_H

#include <HierarchyNode.h>
#include <string>
#include <unordered_map>

class HierarchyStructure
{
private:
    std::string name;
    HierarchyNode *root;
    std::unordered_map<std::string, HierarchyNode *> members;

public:
    HierarchyStructure(std::string name);
    std::string getName();
    HierarchyNode *getRoot();
    std::unordered_map<std::string, HierarchyNode *> *getMembers();
    void setRoot(HierarchyNode *root);
    void addMember(HierarchyNode *member);
    void removeMember(HierarchyNode *member);
    HierarchyNode *getMember(std::string name);
};

#endif