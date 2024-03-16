#ifndef ACCESSRULE_H
#define ACCESSRULE_H

#include <HierarchyNode.h>
#include <Constants.h>

class AccessRule
{
    private:
        CompareType compareType;
        HierarchyNode* node;
        int distance;
};

#endif