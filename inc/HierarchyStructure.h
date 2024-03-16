#ifndef HIERRARCHYSTRUCTURE_H
#define HIERRARCHYSTRUCTURE_H

#include <string>
#include <unordered_map>
#include <HierarchyNode.h>

class HierarchyStructure
{
private:
    std::string name;
    HierarchyNode *root;
    std::unordered_map<std::string, HierarchyNode *> members;
};

#endif