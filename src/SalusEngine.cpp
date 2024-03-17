#include <SalusEngine.h>
#include <HierarchyStructure.h>
#include <iostream>
#include <Logging.h>
#include <Constants.h>

SalusEngine::SalusEngine(std::string topUser)
{
    Logging::init("salus.log", 50, true);
    HierarchyStructure *userHierarchy = new HierarchyStructure("User", nullptr);
    Logging::log(LogLevel::INFO, "Creating Defualt User hierarchy");
    HierarchyNode *topUserNode = new HierarchyNode(topUser, userHierarchy, nullptr);
    userHierarchy->setRoot(topUserNode);
    Logging::log(LogLevel::INFO, "Creating top user: " + topUser);
    hierarchies.insert(std::pair<std::string, HierarchyStructure *>("User", userHierarchy));
}

void SalusEngine::addPieceOfInformation(std::string id, std::string owner,
                                        std::vector<std::string> readAccessList,
                                        std::vector<std::string> writeAccessList)
{
    if (informationBank.find(id) != informationBank.end())
    {
        throw std::runtime_error("Piece of information already exists");
    }
}