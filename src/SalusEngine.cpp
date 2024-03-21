#include <SalusEngine.h>
#include <RuleCollection.h>
#include <PieceOfInformation.h>
#include <HierarchyStructure.h>
#include <iostream>
#include <Logging.h>
#include <Constants.h>

SalusEngine::SalusEngine(std::string topUser)
{
    // Initializing variables
    informationBank = new std::unordered_map<std::string, PieceOfInformation *>();
    ruleCollections = new std::unordered_map<std::string, RuleCollection *>();
    hierarchies = new std::unordered_map<std::string, HierarchyStructure *>();

    // Initializing Engine
    Logging::init("salus.log", 50, true);
    HierarchyStructure *userHierarchy = new HierarchyStructure("User", nullptr);
    Logging::log(LogLevel::INFO, "Creating Defualt User hierarchy");
    HierarchyNode *topUserNode = new HierarchyNode(topUser, userHierarchy, nullptr);
    userHierarchy->setRoot(topUserNode);
    Logging::log(LogLevel::INFO, "Creating top user: " + topUser);
}

void SalusEngine::addPieceOfInformation(std::string id, std::string owner,
                                        std::vector<std::string> readAccessList,
                                        std::vector<std::string> writeAccessList)
{
    if (informationBank->find(id) != informationBank->end())
    {
        Logging::log(LogLevel::ERROR, "Piece of information " + id + " already exists");
        throw std::runtime_error("Piece of information already exists");
    }
    HierarchyNode *ownerNode = hierarchies->at("User")->getMember(owner);
    if (ownerNode == nullptr)
    {
        Logging::log(LogLevel::ERROR, "Owner " + owner + " does not exist");
        throw std::runtime_error("Owner does not exist");
    }
    PieceOfInformation *newPiece = new PieceOfInformation(id, ownerNode);
    for (auto it = readAccessList.begin(); it != readAccessList.end(); it++)
    {
        RuleCollection *ruleCollection = ruleCollections->at(*it);
        if (ruleCollection == nullptr)
        {
            Logging::log(LogLevel::ERROR, "Read Rule Collection " + *it + " does not exist");
            throw std::runtime_error("Read access rule collection does not exist");
        }
        newPiece->addReadAccessRule(*it, ruleCollection);
    }
    for (auto it = writeAccessList.begin(); it != writeAccessList.end(); it++)
    {
        RuleCollection *ruleCollection = ruleCollections->at(*it);
        if (ruleCollection == nullptr)
        {
            Logging::log(LogLevel::ERROR, "Write Rule Collection " + *it + " does not exist");
            throw std::runtime_error("Write access rule collection does not exist");
        }
        newPiece->addWriteAccessRule(*it, ruleCollection);
    }
    informationBank->insert({id, newPiece});
    Logging::log(LogLevel::INFO, "Piece of information " + id + " added successfully");
}

void SalusEngine::removePieceOfInformation(std::string id)
{
    if (informationBank->find(id) == informationBank->end())
    {
        Logging::log(LogLevel::ERROR, "Piece of information " + id + " does not exist");
        throw std::runtime_error("Piece of information does not exist");
    }
    informationBank->erase(id);
    Logging::log(LogLevel::WARN, "Piece of information " + id + " removed!");
}

void SalusEngine::changePieceOfInformationOwner(std::string id, std::string newOwner)
{
    if (informationBank->find(id) == informationBank->end())
    {
        Logging::log(LogLevel::ERROR, "Piece of information " + id + " does not exist");
        throw std::runtime_error("Piece of information does not exist");
    }
    HierarchyNode *newOwnerNode = hierarchies->at("User")->getMember(newOwner);
    if (newOwnerNode == nullptr)
    {
        Logging::log(LogLevel::ERROR, "Owner " + newOwner + " does not exist");
        throw std::runtime_error("Owner does not exist");
    }
    informationBank->at(id)->setOwner(newOwnerNode);
    Logging::log(LogLevel::INFO, "Piece of information " + id + " owner changed to " + newOwner);
}

void SalusEngine::addCollectionToReadAccessList(std::string id, std::string ruleCollectionName)
{
    if (informationBank->find(id) == informationBank->end())
    {
        Logging::log(LogLevel::ERROR, "Piece of information " + id + " does not exist");
        throw std::runtime_error("Piece of information does not exist");
    }
    RuleCollection *ruleCollection = ruleCollections->at(ruleCollectionName);
    if (ruleCollection == nullptr)
    {
        Logging::log(LogLevel::ERROR, "Rule Collection " + ruleCollectionName + " does not exist");
        throw std::runtime_error("Rule collection does not exist");
    }
    informationBank->at(id)->addReadAccessRule(ruleCollectionName, ruleCollection);
    Logging::log(LogLevel::INFO, "Read access rule collection " +
                                     ruleCollectionName + " added to " + id);
}

void SalusEngine::removeCollectionFromReadAccessList(std::string id, std::string ruleCollectionName)
{
    if (informationBank->find(id) == informationBank->end())
    {
        Logging::log(LogLevel::ERROR, "Piece of information " + id + " does not exist");
        throw std::runtime_error("Piece of information does not exist");
    }
    if (informationBank->at(id)->getReadAccessList()->at(ruleCollectionName) == nullptr)
    {
        Logging::log(LogLevel::ERROR, "Read access rule collection " +
                                          ruleCollectionName + " does not exist in " + id);
        throw std::runtime_error("Read access rule collection does not exist");
    }
    informationBank->at(id)->removeReadAccessRule(ruleCollectionName);
    Logging::log(LogLevel::WARN, "Read access rule collection " +
                                     ruleCollectionName + " removed from " + id);
}

void SalusEngine::addCollectionToWriteAccessList(std::string id, std::string ruleCollectionName)
{
    if (informationBank->find(id) == informationBank->end())
    {
        Logging::log(LogLevel::ERROR, "Piece of information " + id + " does not exist");
        throw std::runtime_error("Piece of information does not exist");
    }
    RuleCollection *ruleCollection = ruleCollections->at(ruleCollectionName);
    if (ruleCollection == nullptr)
    {
        Logging::log(LogLevel::ERROR, "Rule Collection " + ruleCollectionName + " does not exist");
        throw std::runtime_error("Rule collection does not exist");
    }
    informationBank->at(id)->addWriteAccessRule(ruleCollectionName, ruleCollection);
    Logging::log(LogLevel::INFO, "Write access rule collection " +
                                     ruleCollectionName + " added to " + id);
}

void SalusEngine::removeCollectionFromWriteAccessList(std::string id,
                                                      std::string ruleCollectionName)
{
    if (informationBank->find(id) == informationBank->end())
    {
        Logging::log(LogLevel::ERROR, "Piece of information " + id + " does not exist");
        throw std::runtime_error("Piece of information does not exist");
    }
    if (informationBank->at(id)->getWriteAccessList()->at(ruleCollectionName) == nullptr)
    {
        Logging::log(LogLevel::ERROR, "Write access rule collection " +
                                          ruleCollectionName + " does not exist in " + id);
        throw std::runtime_error("Write access rule collection does not exist");
    }
    informationBank->at(id)->removeWriteAccessRule(ruleCollectionName);
    Logging::log(LogLevel::WARN, "Write access rule collection " +
                                     ruleCollectionName + " removed from " + id);
}

void SalusEngine::addNewHierarchyStructure(std::string name, std::string root)
{
    if (hierarchies->find(name) != hierarchies->end())
    {
        Logging::log(LogLevel::ERROR, "Hierarchy " + name + " already exists");
        throw std::runtime_error("Hierarchy already exists");
    }
    HierarchyStructure *newHierarchy = new HierarchyStructure(name, nullptr);
    HierarchyNode *rootNode = new HierarchyNode(root, newHierarchy, nullptr);
    newHierarchy->setRoot(rootNode);
    hierarchies->insert({name, newHierarchy});
    Logging::log(LogLevel::INFO, "Hierarchy " + name + " added successfully");
}

void SalusEngine::addNewCriterionForHierarchy(std::string hierarchyName, std::string criterionName,
                                              std::vector<std::string> parentCriterion)
{
    if (hierarchies->find(hierarchyName) == hierarchies->end())
    {
        Logging::log(LogLevel::ERROR, "Hierarchy " + hierarchyName + " does not exist");
        throw std::runtime_error("Hierarchy does not exist");
    }
    HierarchyStructure *hierarchy = hierarchies->at(hierarchyName);
    if (hierarchy == nullptr)
    {
        Logging::log(LogLevel::ERROR, "Hierarchy " + hierarchyName + " does not exist");
        throw std::runtime_error("Hierarchy does not exist");
    }
    if (hierarchy->getMember(criterionName) != nullptr)
    {
        Logging::log(LogLevel::ERROR, "Criterion " + criterionName + " already exists");
        throw std::runtime_error("Criterion already exists");
    }
    std::vector<HierarchyNode *> *parents = new std::vector<HierarchyNode *>();
    for (auto it = parentCriterion.begin(); it != parentCriterion.end(); it++)
    {
        HierarchyNode *parent = hierarchy->getMember(*it);
        if (parent == nullptr)
        {
            Logging::log(LogLevel::ERROR, "Criterion " + *it + " does not exist");
            throw std::runtime_error("Criterion does not exist");
        }
        parents->push_back(parent);
    }
    HierarchyNode *newCriterion = new HierarchyNode(criterionName, hierarchy, parents);
    HierarchyState state = hierarchy->isConsistant();
    if (state != HierarchyState::CONSISTANT)
    {
        for (auto it = parents->begin(); it != parents->end(); it++)
        {
            (*it)->removeChild(newCriterion);
            newCriterion->removeParent(*it);
        }
        std::string message = hierarchy->getInconsistantMessage(state);
        delete newCriterion;
        Logging::log(LogLevel::ERROR, message);
    }
    hierarchy->addMember(newCriterion);
    Logging::log(LogLevel::INFO, "Criterion " + criterionName + " added to " + hierarchyName);
}