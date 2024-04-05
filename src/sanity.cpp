#include <iostream>
#include <SalusEngine.h>
#include <Logging.h>
#include <thread>
#include <iomanip>
#include <sstream>
#include <chrono>

using namespace std;

unsigned int hasher(const string &str)
{
    unsigned int largePrime = 1000000007;
    unsigned int largePrime2 = 1000000009;
    unsigned int hash = 0;
    for (int i = 0; i < (int)str.length(); i++)
    {
        hash += (hash * 256 + largePrime2 * str[i]) % largePrime;
        hash %= largePrime;
    }
    return hash%largePrime;
}

void assert(bool condition, string message)
{
    if (!condition)
    {
        Logging::log(LogLevel::FATAL, message);
        cerr << message << endl;
        this_thread::sleep_for(std::chrono::seconds(2));
        exit(1);
    }
}

int main()
{
    SalusEngine *salusEngine = new SalusEngine("user0");
    string engineName = typeid(salusEngine).name();
    // Check all logging levels
    Logging::log(LogLevel::DEBUG, "This is a debug message");
    Logging::log(LogLevel::INFO, "This is an info message");
    Logging::log(LogLevel::WARN, "This is a warning message");
    Logging::log(LogLevel::ERROR, "This is an error message");
    Logging::log(LogLevel::FATAL, "This is a fatal message");
    Logging::log(LogLevel::WARN, "Engine Name: " + engineName + " Started Successfully!");

    // Add more criterion to User Hierarchy
    salusEngine->addNewCriterionForHierarchy("User", "user1", {"user0"});
    salusEngine->addNewCriterionForHierarchy("User", "user2", {"user0"});
    salusEngine->addNewCriterionForHierarchy("User", "user3", {"user0"});
    // Add 2 ppl per admin
    salusEngine->addNewCriterionForHierarchy("User", "user4", {"user1"});
    salusEngine->addNewCriterionForHierarchy("User", "user5", {"user1"});
    salusEngine->addNewCriterionForHierarchy("User", "user6", {"user2"});
    salusEngine->addNewCriterionForHierarchy("User", "user7", {"user2"});
    salusEngine->addNewCriterionForHierarchy("User", "user8", {"user3"});
    salusEngine->addNewCriterionForHierarchy("User", "user9", {"user3"});

    // Remove user, by removing user 5 and user 6
    salusEngine->removeCriterionFromHierarchy("User", "user8");
    salusEngine->removeCriterionFromHierarchy("User", "user9");
    salusEngine->removeCriterionFromHierarchy("User", "user3");

    // Add clearence level hierarchy
    salusEngine->addNewHierarchyStructure("Clearance", "10");
    for (int i = 9; i >= 0; i--)
    {
        salusEngine->addNewCriterionForHierarchy("Clearance", to_string(i), {to_string(i + 1)});
    }

    // Add roles hierarchy
    salusEngine->addNewHierarchyStructure("Roles", "Super-Admin");
    salusEngine->addNewCriterionForHierarchy("Roles", "Admin1", {"Super-Admin"});
    salusEngine->addNewCriterionForHierarchy("Roles", "Admin2", {"Super-Admin"});
    salusEngine->addNewCriterionForHierarchy("Roles", "Admin3", {"Super-Admin"});
    // Add users with all admins as parents
    salusEngine->addNewCriterionForHierarchy("Roles", "Sub-Admin1", {"Admin1", "Admin2", "Admin3"});
    salusEngine->addNewCriterionForHierarchy("Roles", "Sub-Admin2", {"Admin1", "Admin2", "Admin3"});
    salusEngine->addNewCriterionForHierarchy("Roles", "Sub-Admin3", {"Admin1", "Admin2", "Admin3"});
    salusEngine->addNewCriterionForHierarchy("Roles", "Sub-Admin4", {"Admin1", "Admin2", "Admin3"});
    salusEngine->addNewCriterionForHierarchy("Roles", "Sub-Admin5", {"Admin1", "Admin2", "Admin3"});
    salusEngine->addNewCriterionForHierarchy("Roles", "Sub-Admin6", {"Admin1", "Admin2", "Admin3"});

    // Check hierarchy structure
    assert(hasher(salusEngine->getHierarchyStructure("User")) == 463437768,
           "User Hierarchy is incorrect");
    assert(hasher(salusEngine->getHierarchyStructure("Clearance")) == 648954189,
           "Clearance Hierarchy is incorrect");
    assert(hasher(salusEngine->getHierarchyStructure("Roles")) == 108644618,
           "Roles Hierarchy is incorrect");

    // Create Rule Collections
    salusEngine->addNewRuleCollection("user-rules");
    salusEngine->addNewRuleCollection("clearance-rules");
    salusEngine->addNewRuleCollection("roles-rules");
    
    // Add Access rules to rules collection
    salusEngine->appendRuleToCollection("user-rules", "User", "user0", "<=", 1);
    salusEngine->appendRuleToCollection("user-rules", "User", "user4", ">", 2);
    salusEngine->appendRuleToCollection("user-rules", "User", "user5", "==", 1);
    salusEngine->appendRuleToCollection("clearance-rules", "Clearance", "5", ">", 3);
    salusEngine->appendRuleToCollection("clearance-rules", "Clearance", "5", "<", 2);
    salusEngine->appendRuleToCollection("clearance-rules", "Clearance", "0", ">=", 5);
    salusEngine->appendRuleToCollection("roles-rules", "Roles", "Super-Admin", "==", 1);
    salusEngine->appendRuleToCollection("roles-rules", "Roles", "Admin2", ">", 3);
    salusEngine->appendRuleToCollection("roles-rules", "Roles", "Sub-Admin2", ">=", 2);
   
    assert(939460473 == hasher(salusEngine->getRuleCollection("user-rules")), "User rules not set properly!");
    assert(861244991 == hasher(salusEngine->getRuleCollection("clearance-rules")), "Clearance Rules not set properly!");
    assert(249120230 == hasher(salusEngine->getRuleCollection("roles-rules")), "Roles rules not set properly");

    // Create Piece of Information 
    
    // Wait for Logging to finish
    this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}
