#include <PieceOfInformation.h>

PieceOfInformation::PieceOfInformation(std::string id, HierarchyNode *owner)
{

    this->id = id;
    this->owner = owner;
    this->creationTime = std::time(0);
    this->lastModifiedBy = owner;
    this->lastModifiedTime = std::time(0);
    this->readAccessList = new std::unordered_map<std::string, RuleCollection *>();
    this->writeAccessList = new std::unordered_map<std::string, RuleCollection *>();
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
    return readAccessList;
}

std::unordered_map<std::string, RuleCollection *> *PieceOfInformation::getWriteAccessList()
{
    return writeAccessList;
}

void PieceOfInformation::setOwner(HierarchyNode *owner)
{
    if (owner != nullptr)
    {
        this->owner = owner;
    }
}

void PieceOfInformation::setLastModifiedBy(HierarchyNode *lastModifiedBy)
{
    if (lastModifiedBy != nullptr)
    {
        this->lastModifiedBy = lastModifiedBy;
    }
}

void PieceOfInformation::setLastModifiedTime()
{
    this->lastModifiedTime = std::time(0);
}

void PieceOfInformation::addReadAccessRule(std::string id, RuleCollection *ruleCollection)
{
    if (ruleCollection != nullptr)
    {
        readAccessList->insert(std::pair<std::string, RuleCollection *>(id, ruleCollection));
    }
}

void PieceOfInformation::addWriteAccessRule(std::string id, RuleCollection *ruleCollection)
{
    if (ruleCollection != nullptr)
    {
        writeAccessList->insert(std::pair<std::string, RuleCollection *>(id, ruleCollection));
    }
}

void PieceOfInformation::removeReadAccessRule(std::string id)
{
    readAccessList->erase(id);
}

void PieceOfInformation::removeWriteAccessRule(std::string id)
{
    writeAccessList->erase(id);
}

bool PieceOfInformation::canAccess(HierarchyNode *criterion, AccessType type)
{
    std::unordered_map<std::string, RuleCollection *> *targetList;
    switch (type)
    {
    case READ:
        targetList = readAccessList;
        break;
    case WRITE:
        targetList = writeAccessList;
        break;
    }
    bool accessGranted = false;
    for (auto const &entry : *targetList)
    {
        if (entry.second->canAccess(criterion))
        {
            accessGranted = true;
            break;
        }
    }
    return accessGranted;
}

std::string PieceOfInformation::toString()
{
    std::string creationTimeStr = std::ctime(&creationTime);
    std::string lastModifiedTimeStr = std::ctime(&lastModifiedTime);
    std::string result = "{\n";
    result += "\t'id': '" + getId() + "',\n";
    result += "\t'owner': '" + owner->getName() + "',\n";
    result += "\t'created_at': '" + creationTimeStr + "',\n";
    result += "\t'modified_by': '" + getLastModifiedBy()->getName() + "',\n";
    result += "\t'modified_at': '" + lastModifiedTimeStr + "',\n";
    result += "\t'read_access_list': [";
    for (auto const &entry : *readAccessList)
    {
        result += "'" + entry.second->getName() + "', ";
    }
    result += "],\n";
    result += "\t'write_access_list': [";
    for (auto const &entry : *writeAccessList)
    {
        result += "'" + entry.second->getName() + "', ";
    }
    result += "],\n";
    return result + "\n}";
}
