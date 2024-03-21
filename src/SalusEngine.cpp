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
        std::string message = "Piece of information " + id + " already exists";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    HierarchyNode *ownerNode = hierarchies->at("User")->getMember(owner);
    if (ownerNode == nullptr)
    {
        std::string message = "Owner " + owner + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    PieceOfInformation *newPiece = new PieceOfInformation(id, ownerNode);
    for (auto it = readAccessList.begin(); it != readAccessList.end(); it++)
    {
        RuleCollection *ruleCollection = ruleCollections->at(*it);
        if (ruleCollection == nullptr)
        {
            std::string message = "Read Rule Collection " + *it + " does not exist";
            Logging::log(LogLevel::ERROR, message);
            throw std::runtime_error(message);
        }
        newPiece->addReadAccessRule(*it, ruleCollection);
    }
    for (auto it = writeAccessList.begin(); it != writeAccessList.end(); it++)
    {
        RuleCollection *ruleCollection = ruleCollections->at(*it);
        if (ruleCollection == nullptr)
        {
            std::string message = "Write Rule Collection " + *it + " does not exist";
            Logging::log(LogLevel::ERROR, message);
            throw std::runtime_error(message);
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
        std::string message = "Piece of information " + id + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    informationBank->erase(id);
    Logging::log(LogLevel::WARN, "Piece of information " + id + " removed!");
}

void SalusEngine::changePieceOfInformationOwner(std::string id, std::string newOwner)
{
    if (informationBank->find(id) == informationBank->end())
    {
        std::string message = "Piece of information " + id + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    HierarchyNode *newOwnerNode = hierarchies->at("User")->getMember(newOwner);
    if (newOwnerNode == nullptr)
    {
        std::string message = "Owner " + newOwner + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    informationBank->at(id)->setOwner(newOwnerNode);
    Logging::log(LogLevel::INFO, "Piece of information " + id + " owner changed to " + newOwner);
}

void SalusEngine::addCollectionToReadAccessList(std::string id, std::string ruleCollectionName)
{
    if (informationBank->find(id) == informationBank->end())
    {
        std::string message = "Piece of information " + id + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    RuleCollection *ruleCollection = ruleCollections->at(ruleCollectionName);
    if (ruleCollection == nullptr)
    {
        std::string message = "Rule Collection " + ruleCollectionName + " does not exist ";
        Logging::log(LogLevel::ERROR, message);
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
        std::string message = "Piece of information " + id + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    if (informationBank->at(id)->getReadAccessList()->at(ruleCollectionName) == nullptr)
    {
        std::string message = "Read access rule collection " +
                              ruleCollectionName + " does not exist in " + id;
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    informationBank->at(id)->removeReadAccessRule(ruleCollectionName);
    Logging::log(LogLevel::WARN, "Read access rule collection " +
                                     ruleCollectionName + " removed from " + id);
}

void SalusEngine::addCollectionToWriteAccessList(std::string id, std::string ruleCollectionName)
{
    if (informationBank->find(id) == informationBank->end())
    {
        std::string message = "Piece of information " + id + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    RuleCollection *ruleCollection = ruleCollections->at(ruleCollectionName);
    if (ruleCollection == nullptr)
    {
        std::string message = "Rule Collection " + ruleCollectionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
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
        std::string message = "Piece of information " + id + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    if (informationBank->at(id)->getWriteAccessList()->at(ruleCollectionName) == nullptr)
    {
        std::string message = "Write access rule collection " +
                              ruleCollectionName + " does not exist in " + id;
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    informationBank->at(id)->removeWriteAccessRule(ruleCollectionName);
    Logging::log(LogLevel::WARN, "Write access rule collection " +
                                     ruleCollectionName + " removed from " + id);
}

void SalusEngine::addNewHierarchyStructure(std::string name, std::string root)
{
    if (hierarchies->find(name) != hierarchies->end())
    {
        std::string message = "Hierarchy " + name + " already exists";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
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
        std::string message = "Hierarchy " + hierarchyName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    HierarchyStructure *hierarchy = hierarchies->at(hierarchyName);
    if (hierarchy->getMember(criterionName) != nullptr)
    {
        std::string message = "Criterion " + criterionName + " already exists";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    std::vector<HierarchyNode *> *parents = new std::vector<HierarchyNode *>();
    for (auto it = parentCriterion.begin(); it != parentCriterion.end(); it++)
    {
        HierarchyNode *parent = hierarchy->getMember(*it);
        if (parent == nullptr)
        {
            std::string message = "Criterion " + *it + " does not exist";
            Logging::log(LogLevel::ERROR, message);
            throw std::runtime_error(message);
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

void SalusEngine::removeCriterionFromHierarchy(std::string hierarchyName, std::string criterionName)
{
    if (hierarchies->find(hierarchyName) == hierarchies->end())
    {
        std::string message = "Hierarchy " + hierarchyName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    HierarchyStructure *hierarchy = hierarchies->at(hierarchyName);
    HierarchyNode *targetNode = hierarchy->getMember(criterionName);
    if (targetNode == nullptr)
    {
        std::string message = "Criterion " + criterionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    if (targetNode->getChildren()->size() != 0)
    {
        std::string message = "Criterion " + criterionName + " is not on the edge!";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    for (auto it = targetNode->getParents()->begin(); it != targetNode->getParents()->end(); it++)
    {
        it->second->removeChild(targetNode);
    }
    // Remove all access rules with this criterion
    for (auto it = ruleCollections->begin(); it != ruleCollections->end(); it++)
    {
        RuleCollection *ruleCollection = it->second;
        std::vector<int> indicesToRemove = std::vector<int>();
        for (int i = 0; i < ruleCollection->getRules()->size(); i++)
        {
            if (ruleCollection->getRules()->at(i)->getNode() == targetNode)
            {
                indicesToRemove.push_back(i);
            }
        }
        for (auto it = indicesToRemove.begin(); it != indicesToRemove.end(); it++)
        {
            ruleCollection->getRules()->erase(ruleCollection->getRules()->begin() + *it);
        }
    }
    delete targetNode;
    hierarchy->removeMember(criterionName);
    Logging::log(LogLevel::WARN, "Criterion " + criterionName + " removed from " + hierarchyName);
}

void SalusEngine::renameCriterionFromHierarchy(std::string hierarchyName, std::string criterionName,
                                               std::string newCriterionName)
{
    if (hierarchies->find(hierarchyName) == hierarchies->end())
    {
        std::string message = "Hierarchy " + hierarchyName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    HierarchyStructure *hierarchy = hierarchies->at(hierarchyName);
    HierarchyNode *targetNode = hierarchy->getMember(criterionName);
    if (targetNode == nullptr)
    {
        std::string message = "Criterion " + criterionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    if (hierarchy->getMember(newCriterionName) != nullptr)
    {
        std::string message = "Criterion " + newCriterionName + " already exists";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    targetNode->setName(newCriterionName);
    hierarchy->addMember(targetNode);
    Logging::log(LogLevel::WARN, "Criterion " + criterionName + " renamed to " + newCriterionName);
}

void SalusEngine::changeCriterionParents(std::string hierarchyName, std::string criterionName,
                                         std::vector<std::string> newParents)
{
    if (hierarchies->find(hierarchyName) == hierarchies->end())
    {
        std::string message = "Hierarchy " + hierarchyName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    HierarchyStructure *hierarchy = hierarchies->at(hierarchyName);
    HierarchyNode *targetNode = hierarchy->getMember(criterionName);
    if (targetNode == nullptr)
    {
        std::string message = "Criterion " + criterionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    std::vector<HierarchyNode *> *newParentsNodes = new std::vector<HierarchyNode *>();
    for (auto it = newParents.begin(); it != newParents.end(); it++)
    {
        HierarchyNode *parent = hierarchy->getMember(*it);
        if (parent == nullptr)
        {
            std::string message = "Criterion " + *it + " does not exist";
            Logging::log(LogLevel::ERROR, message);
            throw std::runtime_error(message);
        }
        newParentsNodes->push_back(parent);
    }
    std::vector<HierarchyNode *> *oldParents = new std::vector<HierarchyNode *>();
    for (auto it = targetNode->getParents()->begin(); it != targetNode->getParents()->end(); it++)
    {
        oldParents->push_back(it->second);
    }
    targetNode->removeParents(oldParents);
    targetNode->addParents(newParentsNodes);
    HierarchyState state = hierarchy->isConsistant();
    if (state != HierarchyState::CONSISTANT)
    {
        targetNode->removeParents(newParentsNodes);
        targetNode->addParents(oldParents);
        std::string message = hierarchy->getInconsistantMessage(state);
        Logging::log(LogLevel::ERROR, message);
    }
    Logging::log(LogLevel::WARN, "Criterion " + criterionName + " parents changed");
}

void SalusEngine::removeHierarchy(std::string name)
{
    if (hierarchies->find(name) == hierarchies->end())
    {
        std::string message = "Hierarchy " + name + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        throw std::runtime_error(message);
    }
    // For all criterion remove all corresponding Access Rules
    HierarchyStructure *hierarchy = hierarchies->at(name);
    for (auto it = hierarchy->getMembers()->begin(); it != hierarchy->getMembers()->end(); it++)
    {
        HierarchyNode *criterion = it->second;
        for (auto it = ruleCollections->begin(); it != ruleCollections->end(); it++)
        {
            RuleCollection *ruleCollection = it->second;
            std::vector<int> indicesToRemove = std::vector<int>();
            for (int i = 0; i < ruleCollection->getRules()->size(); i++)
            {
                if (ruleCollection->getRules()->at(i)->getNode() == criterion)
                {
                    indicesToRemove.push_back(i);
                }
            }
            for (auto it = indicesToRemove.begin(); it != indicesToRemove.end(); it++)
            {
                ruleCollection->getRules()->erase(ruleCollection->getRules()->begin() + *it);
            }
        }
    }
    delete hierarchy;
    hierarchies->erase(name);
    Logging::log(LogLevel::WARN, "Hierarchy " + name + " removed");
}