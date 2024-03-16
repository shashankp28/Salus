#ifndef LOGGING_H
#define LOGGING_H

#include <Constants.h>
#include <fstream>
#include <string>
#include <mutex>

class Logging
{

private:
    static std::ofstream logFile;
    static std::mutex logMutex;

public:
    static void log(std::string message, LogLevel level = LogLevel::INFO);
};

#endif