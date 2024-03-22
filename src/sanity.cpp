#include <iostream>
#include <SalusEngine.h>
#include <Logging.h>
#include <thread>
#include <chrono>

using namespace std;

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
    salusEngine->addNewCriterionForHierarchy("Roles", "User1", {"Admin1", "Admin2", "Admin3"});
    salusEngine->addNewCriterionForHierarchy("Roles", "User2", {"Admin1", "Admin2", "Admin3"});
    salusEngine->addNewCriterionForHierarchy("Roles", "User3", {"Admin1", "Admin2", "Admin3"});
    salusEngine->addNewCriterionForHierarchy("Roles", "User4", {"Admin1", "Admin2", "Admin3"});
    salusEngine->addNewCriterionForHierarchy("Roles", "User5", {"Admin1", "Admin2", "Admin3"});

    cout << salusEngine->getHierarchy("Roles") << endl;

    // Wait for Logging to finish
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}