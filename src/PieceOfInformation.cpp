#include <PieceOfInformation.h>

PieceOfInformation::PieceOfInformation(std::string id, HierarchyNode *owner)
{
    this->id = id;
    this->owner = owner;
    this->creationTime = std::time(0);
    this->lastModifiedBy = owner;
    this->lastModifiedTime = std::time(0);
}

std::string PieceOfInformation::getId()
{
    return id;
}

HierarchyNode *PieceOfInformation::getOwner()
{
    return owner;
}

std::time_t PieceOfInformation::getCreationTime()
{
    return creationTime;
}

HierarchyNode *PieceOfInformation::getLastModifiedBy()
{
    return lastModifiedBy;
}

std::time_t PieceOfInformation::getLastModifiedTime()
{
    return lastModifiedTime;
}

std::unordered_map<std::string, RuleCollection *> *PieceOfInformation::getReadAccessList()
{
    return &readAccessList;
}

std::unordered_map<std::string, RuleCollection *> *PieceOfInformation::getWriteAccessList()
{
    return &writeAccessList;
}

void PieceOfInformation::setOwner(HierarchyNode *owner)
{
    this->owner = owner;
}

void PieceOfInformation::setLastModifiedBy(HierarchyNode *lastModifiedBy)
{
    this->lastModifiedBy = lastModifiedBy;
}

void PieceOfInformation::setLastModifiedTime(std::time_t lastModifiedTime)
{
    this->lastModifiedTime = lastModifiedTime;
}

void PieceOfInformation::addReadAccessRule(std::string userId, RuleCollection *ruleCollection)
{
    if (ruleCollection != nullptr)
    {
        readAccessList[userId] = ruleCollection;
    }
}

void PieceOfInformation::addWriteAccessRule(std::string userId, RuleCollection *ruleCollection)
{
    if (ruleCollection != nullptr)
    {
        writeAccessList[userId] = ruleCollection;
    }
}

void PieceOfInformation::removeReadAccessRule(std::string userId)
{
    readAccessList.erase(userId);
}

void PieceOfInformation::removeWriteAccessRule(std::string userId)
{
    writeAccessList.erase(userId);
}
