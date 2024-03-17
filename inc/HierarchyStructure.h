#ifndef HIERRARCHYSTRUCTURE_H
#define HIERRARCHYSTRUCTURE_H

#include <string>
#include <unordered_map>

class HierarchyNode;

class HierarchyStructure
{
private:
    std::string name;
    HierarchyNode *root;
    std::unordered_map<std::string, HierarchyNode *> members;

public:
    HierarchyStructure(std::string name, HierarchyNode *root);
    std::string getName();
    HierarchyNode *getRoot();
    HierarchyNode *getMember(std::string name);
    std::unordered_map<std::string, HierarchyNode *> *getMembers();
    void setRoot(HierarchyNode *root);
    void addMember(HierarchyNode *member);
    void removeMember(HierarchyNode *member);
    void removeMember(std::string name);
};

#endif