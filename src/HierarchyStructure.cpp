#include <HierarchyNode.h>
#include <HierarchyStructure.h>
#include <queue>
#include <Logging.h>

HierarchyStructure::HierarchyStructure(std::string name, HierarchyNode *root)
{
    this->name = name;
    this->members = new std::unordered_map<std::string, HierarchyNode *>();
    this->setRoot(root);
    this->addMember(root);
}

std::string HierarchyStructure::getName()
{
    return name;
}

HierarchyNode *HierarchyStructure::getRoot()
{
    return root;
}

HierarchyNode *HierarchyStructure::getMember(std::string name)
{
    if (members->find(name) == members->end())
    {
        return nullptr;
    }
    return members->at(name);
}

std::unordered_map<std::string, HierarchyNode *> *HierarchyStructure::getMembers()
{
    return members;
}

void HierarchyStructure::setRoot(HierarchyNode *root)
{
    this->root = root;
}

void HierarchyStructure::addMember(HierarchyNode *member)
{
    if (member != nullptr)
    {
        members->insert(std::pair<std::string, HierarchyNode *>(member->getName(), member));
    }
}

void HierarchyStructure::removeMember(HierarchyNode *member)
{
    if (member != nullptr)
    {
        members->erase(member->getName());
    }
}

void HierarchyStructure::removeMember(std::string name)
{
    members->erase(name);
}

HierarchyState HierarchyStructure::isConsistant()
{
    if (!isRootHighest())
    {
        return HierarchyState::LOW_ROOT;
    }
    if (hasCycle())
    {
        return HierarchyState::CYCLE;
    }
    if (!allNodesReachable())
    {
        return HierarchyState::DISJOINT;
    }
    return HierarchyState::CONSISTANT;
}

bool HierarchyStructure::isRootHighest()
{
    // Except for the root, all nodes must have at least one parent
    for (auto it = members->begin(); it != members->end(); it++)
    {
        if (it->second->getParents()->size() == 0 && it->second != root)
        {
            return false;
        }
    }
    return true;
}

bool HierarchyStructure::allNodesReachable()
{
    // All nodes must be reachable from the root
    std::unordered_map<std::string, bool> visited;
    for (auto it = members->begin(); it != members->end(); it++)
    {
        visited.insert({it->first, false});
    }
    std::queue<HierarchyNode *> queue;
    queue.push(root);
    while (!queue.empty())
    {
        HierarchyNode *current = queue.front();
        queue.pop();
        visited[current->getName()] = true;
        for (auto it = current->getChildren()->begin(); it != current->getChildren()->end(); it++)
        {
            if (!visited[it->first])
            {
                queue.push(it->second);
            }
        }
    }
    for (auto it = visited.begin(); it != visited.end(); it++)
    {
        if (!it->second)
        {
            return false;
        }
    }
    return true;
}

bool HierarchyStructure::hasCycle()
{
    // The graph must be a DAG
    std::unordered_map<std::string, int> inDegree;
    for (auto it = members->begin(); it != members->end(); it++)
    {
        inDegree.insert({it->first, it->second->getParents()->size()});
    }
    std::queue<HierarchyNode *> queue;
    for (auto it = inDegree.begin(); it != inDegree.end(); it++)
    {
        if (it->second == 0)
        {
            queue.push(members->at(it->first));
        }
    }
    int count = 0;
    while (!queue.empty())
    {
        HierarchyNode *current = queue.front();
        queue.pop();
        count++;
        for (auto it = current->getChildren()->begin(); it != current->getChildren()->end(); it++)
        {
            inDegree[it->first]--;
            if (inDegree[it->first] == 0)
            {
                queue.push(it->second);
            }
        }
    }
    return count != (int)members->size();
}

std::string HierarchyStructure::getInconsistantMessage(HierarchyState state)
{
    std::string message;
    switch (state)
    {
    case HierarchyState::LOW_ROOT:
        message = "Hierarchy " + name + " has a node with no parent";
        break;
    case HierarchyState::CYCLE:
        message = "Hierarchy " + name + " has a cycle";
        break;
    case HierarchyState::DISJOINT:
        message = "Hierarchy " + name + " has disjoint nodes";
        break;
    default:
        break;
    }
    Logging::log(LogLevel::ERROR, message);
    return message;
}

std::string HierarchyStructure::toString()
{
    std::string str = "Hierarchy " + name + ":\n";
    HierarchyNode *root = getRoot();
    std::queue<std::pair<HierarchyNode *, int>> queue;
    queue.push({root, 0});
    std::unordered_map<int, std::vector<HierarchyNode *>> levels;
    while (!queue.empty())
    {
        std::pair<HierarchyNode *, int> current = queue.front();
        queue.pop();
        if (levels.find(current.second) == levels.end())
        {
            levels.insert({current.second, std::vector<HierarchyNode *>()});
        }
        levels[current.second].push_back(current.first);
        for (int i = 0; i < current.second; i++)
        {
            str += "  ";
        }
        str += current.first->getName() + "\n";
        for (auto it = current.first->getChildren()->begin(); it != current.first->getChildren()->end(); it++)
        {
            queue.push({it->second, current.second + 1});
        }
    }
    std::string levelStr = "";
    for (auto it = levels.begin(); it != levels.end(); it++)
    {
        levelStr += "Level " + std::to_string(it->first) + ": ";
        for (auto jt = it->second.begin(); jt != it->second.end(); jt++)
        {
            levelStr += (*jt)->getName() + " ";
        }
        levelStr += "\n";
    }
    return str;
}