#include <iostream>
#include <SalusEngine.h>
#include <Logging.h>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    SalusEngine *salusEngine = new SalusEngine("rootUser");
    string engineName = typeid(salusEngine).name();
    // Check all logging levels
    Logging::log(LogLevel::DEBUG, "This is a debug message");
    Logging::log(LogLevel::INFO, "This is an info message");
    Logging::log(LogLevel::WARN, "This is a warning message");
    Logging::log(LogLevel::ERROR, "This is an error message");
    Logging::log(LogLevel::FATAL, "This is a fatal message");
    Logging::log(LogLevel::WARN, "Engine Name: " + engineName + " Started Successfully!");

    // Add more criterion to User Hierarchy
    salusEngine->addNewCriterionForHierarchy("User", "Admin1", {"root"});
    salusEngine->addNewCriterionForHierarchy("User", "Admin2", {"root"});
    salusEngine->addNewCriterionForHierarchy("User", "Admin3", {"root"});
    // Add 2 ppl per admin
    salusEngine->addNewCriterionForHierarchy("User", "User1", {"Admin1"});
    salusEngine->addNewCriterionForHierarchy("User", "User2", {"Admin1"});
    salusEngine->addNewCriterionForHierarchy("User", "User3", {"Admin2"});
    salusEngine->addNewCriterionForHierarchy("User", "User4", {"Admin2"});
    salusEngine->addNewCriterionForHierarchy("User", "User5", {"Admin3"});
    salusEngine->addNewCriterionForHierarchy("User", "User6", {"Admin3"});

    

    // Wait for Logging to finish
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}