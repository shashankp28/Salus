#ifndef LOGGING_H
#define LOGGING_H

#include <fstream>
#include <string>
#include <mutex>
#include <Constants.h>

class Logging
{

private:
    static std::string logFilePath;
    static std::ofstream logFile;
    static std::mutex logMutex;
    static unsigned maxFileSize;
    static void checkMove();
    static std::string getLevelString(LogLevel level);
    static std::string getTimeString();
    static void logHelper(std::string message, LogLevel level = LogLevel::INFO);

public:
    static void init(std::string logFileName, unsigned maxFileSize, bool clearPrevious = false);
    static void log(std::string message, LogLevel level = LogLevel::INFO);
};

#endif