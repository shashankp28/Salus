#include <SalusEngine.h>
#include <RuleCollection.h>
#include <PieceOfInformation.h>
#include <HierarchyStructure.h>
#include <iostream>
#include <Logging.h>
#include <Constants.h>
#include <thread>
#include <chrono>
#include <AccessRule.h>

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
    userHierarchy->addMember(topUserNode);
    hierarchies->insert({"User", userHierarchy});
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
        shutdown(message);
    }
    HierarchyNode *ownerNode = hierarchies->at("User")->getMember(owner);
    if (ownerNode == nullptr)
    {
        std::string message = "Owner " + owner + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    PieceOfInformation *newPiece = new PieceOfInformation(id, ownerNode);
    for (auto it = readAccessList.begin(); it != readAccessList.end(); it++)
    {
        RuleCollection *ruleCollection = ruleCollections->at(*it);
        if (ruleCollection == nullptr)
        {
            std::string message = "Read Rule Collection " + *it + " does not exist";
            Logging::log(LogLevel::ERROR, message);
            shutdown(message);
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
            shutdown(message);
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
        shutdown(message);
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
        shutdown(message);
    }
    HierarchyNode *newOwnerNode = hierarchies->at("User")->getMember(newOwner);
    if (newOwnerNode == nullptr)
    {
        std::string message = "Owner " + newOwner + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
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
        shutdown(message);
    }
    RuleCollection *ruleCollection = ruleCollections->at(ruleCollectionName);
    if (ruleCollection == nullptr)
    {
        std::string message = "Rule Collection " + ruleCollectionName + " does not exist ";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
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
        shutdown(message);
    }
    if (informationBank->at(id)->getReadAccessList()->at(ruleCollectionName) == nullptr)
    {
        std::string message = "Read access rule collection " +
                              ruleCollectionName + " does not exist in " + id;
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
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
        shutdown(message);
    }
    RuleCollection *ruleCollection = ruleCollections->at(ruleCollectionName);
    if (ruleCollection == nullptr)
    {
        std::string message = "Rule Collection " + ruleCollectionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
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
        shutdown(message);
    }
    if (informationBank->at(id)->getWriteAccessList()->at(ruleCollectionName) == nullptr)
    {
        std::string message = "Write access rule collection " +
                              ruleCollectionName + " does not exist in " + id;
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
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
        shutdown(message);
    }
    HierarchyStructure *newHierarchy = new HierarchyStructure(name, nullptr);
    HierarchyNode *rootNode = new HierarchyNode(root, newHierarchy, nullptr);
    newHierarchy->setRoot(rootNode);
    hierarchies->insert({name, newHierarchy});
    hierarchies->at(name)->addMember(rootNode);
    Logging::log(LogLevel::INFO, "Hierarchy " + name + " added successfully");
}

void SalusEngine::addNewCriterionForHierarchy(std::string hierarchyName, std::string criterionName,
                                              std::vector<std::string> parentCriterion)
{
    if (hierarchies->find(hierarchyName) == hierarchies->end())
    {
        std::string message = "Hierarchy " + hierarchyName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    HierarchyStructure *hierarchy = hierarchies->at(hierarchyName);
    if (hierarchy->getMember(criterionName) != nullptr)
    {
        std::string message = "Criterion " + criterionName + " already exists";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    std::vector<HierarchyNode *> *parents = new std::vector<HierarchyNode *>();
    for (auto it = parentCriterion.begin(); it != parentCriterion.end(); it++)
    {
        HierarchyNode *parent = hierarchy->getMember(*it);
        if (parent == nullptr)
        {
            std::string message = "Criterion " + *it + " does not exist";
            Logging::log(LogLevel::ERROR, message);
            shutdown(message);
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
        shutdown(message);
    }
    HierarchyStructure *hierarchy = hierarchies->at(hierarchyName);
    HierarchyNode *targetNode = hierarchy->getMember(criterionName);
    if (targetNode == nullptr)
    {
        std::string message = "Criterion " + criterionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    if (targetNode->getChildren()->size() != 0)
    {
        std::string message = "Criterion " + criterionName +
                              " is not on the edge, cannot be removed!";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
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
        for (int i = 0; i < (int)ruleCollection->getRules()->size(); i++)
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
        shutdown(message);
    }
    HierarchyStructure *hierarchy = hierarchies->at(hierarchyName);
    HierarchyNode *targetNode = hierarchy->getMember(criterionName);
    if (targetNode == nullptr)
    {
        std::string message = "Criterion " + criterionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    if (hierarchy->getMember(newCriterionName) != nullptr)
    {
        std::string message = "Criterion " + newCriterionName + " already exists";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
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
        shutdown(message);
    }
    HierarchyStructure *hierarchy = hierarchies->at(hierarchyName);
    HierarchyNode *targetNode = hierarchy->getMember(criterionName);
    if (targetNode == nullptr)
    {
        std::string message = "Criterion " + criterionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    std::vector<HierarchyNode *> *newParentsNodes = new std::vector<HierarchyNode *>();
    for (auto it = newParents.begin(); it != newParents.end(); it++)
    {
        HierarchyNode *parent = hierarchy->getMember(*it);
        if (parent == nullptr)
        {
            std::string message = "Criterion " + *it + " does not exist";
            Logging::log(LogLevel::ERROR, message);
            shutdown(message);
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
        shutdown(message);
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
            for (int i = 0; i < (int)ruleCollection->getRules()->size(); i++)
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

void SalusEngine::addNewRuleCollection(std::string name)
{
    if (ruleCollections->find(name) != ruleCollections->end())
    {
        std::string message = "Rule Collection " + name + " already exists";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    RuleCollection *newCollection = new RuleCollection(name);
    ruleCollections->insert({name, newCollection});
    Logging::log(LogLevel::INFO, "Rule Collection " + name + " added successfully");
}

void SalusEngine::appendRuleToCollection(std::string collectionName, std::string hierarchyName,
                                         std::string criterionName, std::string compareType,
                                         int distacne)
{
    if (ruleCollections->find(collectionName) == ruleCollections->end())
    {
        std::string message = "Rule Collection " + collectionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    RuleCollection *ruleCollection = ruleCollections->at(collectionName);
    HierarchyStructure *hierarchy = hierarchies->at(hierarchyName);
    if (hierarchy == nullptr)
    {
        std::string message = "Hierarchy " + hierarchyName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    HierarchyNode *criterion = hierarchy->getMember(criterionName);
    if (criterion == nullptr)
    {
        std::string message = "Criterion " + criterionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    CompareType type = CompareType::EQUAL;
    if (compareType == "==")
    {
        type = CompareType::EQUAL;
    }
    else if (compareType == "!=")
    {
        type = CompareType::NOT_EQUAL;
    }
    else if (compareType == ">")
    {
        type = CompareType::GREATER;
    }
    else if (compareType == "<")
    {
        type = CompareType::LESS;
    }
    else if (compareType == ">=")
    {
        type = CompareType::GREATER_EQUAL;
    }
    else if (compareType == "<=")
    {
        type = CompareType::LESS_EQUAL;
    }
    else
    {
        std::string message = "Invalid compare type " + compareType;
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    AccessRule *newRule = new AccessRule(criterion, type, distacne);
    ruleCollection->addRule(newRule);
    Logging::log(LogLevel::INFO, "Rule added to " + collectionName);
}

void SalusEngine::removeRuleFromCollection(std::string collectionName, int index)
{
    if (ruleCollections->find(collectionName) == ruleCollections->end())
    {
        std::string message = "Rule Collection " + collectionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    RuleCollection *ruleCollection = ruleCollections->at(collectionName);
    if (index < 0 || index >= (int)ruleCollection->getRules()->size())
    {
        std::string message = "Index out of bounds";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    ruleCollection->getRules()->erase(ruleCollection->getRules()->begin() + index);
    Logging::log(LogLevel::WARN, "Rule removed from " + collectionName);
}

void SalusEngine::removeRuleCollection(std::string name)
{
    if (ruleCollections->find(name) == ruleCollections->end())
    {
        std::string message = "Rule Collection " + name + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    RuleCollection *targetRuleCollection = ruleCollections->at(name);
    // Remove Rule collection from all Piece of Information
    for (auto it = informationBank->begin(); it != informationBank->end(); it++)
    {
        PieceOfInformation *piece = it->second;
        piece->removeReadAccessRule(name);
        piece->removeWriteAccessRule(name);
    }
    delete targetRuleCollection;
    Logging::log(LogLevel::WARN, "Rule Collection " + name + " removed");
}

bool SalusEngine::canRead(std::string hierarchyName, std::string criterionName, std::string id)
{
    if (informationBank->find(id) == informationBank->end())
    {
        std::string message = "Piece of information " + id + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    PieceOfInformation *piece = informationBank->at(id);
    if (hierarchies->find(hierarchyName) == hierarchies->end())
    {
        std::string message = "Hierarchy " + hierarchyName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    HierarchyNode *criterion = hierarchies->at(hierarchyName)->getMember(criterionName);
    if (criterion == nullptr)
    {
        std::string message = "Criterion " + criterionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    bool result = piece->canAccess(criterion, AccessType::READ);
    if (result)
    {
        Logging::log(LogLevel::DEBUG, "Criterion: " + hierarchyName +
                                          "::" + criterionName + " can read Info:" + id);
    }
    else
    {
        Logging::log(LogLevel::WARN, "Criterion: " + hierarchyName +
                                         "::" + criterionName + " can not read Info: " + id);
    }
    return result;
}

bool SalusEngine::canWrite(std::string username, std::string hierarchyName,
                           std::string criterionName, std::string id)
{
    if (informationBank->find(id) == informationBank->end())
    {
        std::string message = "Piece of information " + id + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    PieceOfInformation *piece = informationBank->at(id);
    if (hierarchies->find(hierarchyName) == hierarchies->end())
    {
        std::string message = "Hierarchy " + hierarchyName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    HierarchyNode *criterion = hierarchies->at(hierarchyName)->getMember(criterionName);
    if (criterion == nullptr)
    {
        std::string message = "Criterion " + criterionName + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    HierarchyNode *user = hierarchies->at("User")->getMember(username);
    if (user == nullptr)
    {
        std::string message = "User " + username + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    bool result = piece->canAccess(criterion, AccessType::WRITE);
    if (result)
    {
        Logging::log(LogLevel::DEBUG, "User: " + username + " can write to Criterion: " +
                                          hierarchyName + "::" + criterionName + " Info:" + id);
        piece->setLastModifiedBy(user);
        piece->setLastModifiedTime();
    }
    else
    {
        Logging::log(LogLevel::WARN, "User: " + username + " can not write to Criterion: " +
                                         hierarchyName + "::" + criterionName + " Info:" + id);
    }
    return result;
}

std::string SalusEngine::getPieceOfInformation(std::string id)
{
    if (informationBank->find(id) == informationBank->end())
    {
        std::string message = "Piece of information " + id + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    PieceOfInformation *piece = informationBank->at(id);
    std::string result = piece->toString();
    Logging::log(LogLevel::INFO, "Piece of information metadata " + id + " retrieved");
    return result;
}

std::string SalusEngine::getRuleCollection(std::string name)
{
    if (ruleCollections->find(name) == ruleCollections->end())
    {
        std::string message = "Rule Collection " + name + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    RuleCollection *collection = ruleCollections->at(name);
    std::string result = collection->toString();
    Logging::log(LogLevel::INFO, "Rule Collection metadata " + name + " retrieved");
    return result;
}

std::string SalusEngine::getHierarchy(std::string name)
{
    if (hierarchies->find(name) == hierarchies->end())
    {
        std::string message = "Hierarchy " + name + " does not exist";
        Logging::log(LogLevel::ERROR, message);
        shutdown(message);
    }
    HierarchyStructure *hierarchy = hierarchies->at(name);
    std::string result = hierarchy->toString();
    Logging::log(LogLevel::INFO, "Hierarchy metadata " + name + " retrieved");
    return result;
}

std::vector<std::string> SalusEngine::showAllHierarchies()
{
    std::vector<std::string> result = std::vector<std::string>();
    for (auto it = hierarchies->begin(); it != hierarchies->end(); it++)
    {
        result.push_back(it->first);
    }
    Logging::log(LogLevel::INFO, "All Hierarchies retrieved");
    return result;
}
std::vector<std::string> SalusEngine::showAllRuleCollections()
{
    std::vector<std::string> result = std::vector<std::string>();
    for (auto it = ruleCollections->begin(); it != ruleCollections->end(); it++)
    {
        result.push_back(it->first);
    }
    Logging::log(LogLevel::INFO, "All Rule Collections retrieved");
    return result;
}

void SalusEngine::shutdown(std::string message)
{
    delete informationBank;
    delete ruleCollections;
    delete hierarchies;
    // Wait for logs to finish
    std::this_thread::sleep_for(std::chrono::seconds(2));
    throw std::runtime_error(message);
}