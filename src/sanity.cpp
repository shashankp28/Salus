#include <iostream>
#include <SalusEngine.h>
#include <Logging.h>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    SalusEngine *salusEngine = new SalusEngine("shashankp@gmail.com");
    string engineName = typeid(salusEngine).name();
    // Check all logging levels
    Logging::log(LogLevel::DEBUG, "This is a debug message");
    Logging::log(LogLevel::INFO, "This is an info message");
    Logging::log(LogLevel::WARN, "This is a warning message");
    Logging::log(LogLevel::ERROR, "This is an error message");
    Logging::log(LogLevel::FATAL, "This is a fatal message");
    Logging::log(LogLevel::WARN, "Engine Name: " + engineName + " Started Successfully!");


    

    // Wait for Logging to finish
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}