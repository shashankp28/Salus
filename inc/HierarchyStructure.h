#ifndef HIERRARCHYSTRUCTURE_H
#define HIERRARCHYSTRUCTURE_H

#include <string>
#include <Constants.h>
#include <unordered_map>

class HierarchyNode;

class HierarchyStructure
{
private:
    std::string name;
    HierarchyNode *root;
    std::unordered_map<std::string, HierarchyNode *> *members;
    bool isRootHighest();
    bool hasCycle();
    bool allNodesReachable();

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
    HierarchyState isConsistant();
    std::string getInconsistantMessage(HierarchyState state);
};

#endif