#include <SalusEngine.h>
#include <HierarchyStructure.h>

SalusEngine::SalusEngine(std::string topUser)
{
    HierarchyStructure *userHierarchy = new HierarchyStructure("User", nullptr);
    HierarchyNode *topUserNode = new HierarchyNode(topUser, userHierarchy, nullptr);
    userHierarchy->setRoot(topUserNode);
    hierarchies.insert(std::pair<std::string, HierarchyStructure *>("User", userHierarchy));
}