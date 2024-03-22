#ifndef LOGGING_H
#define LOGGING_H

#include <Constants.h>
#include <fstream>
#include <string>
#include <mutex>
#include <queue>

class Logging
{

private:
    static std::string logFilePath;
    static std::ofstream logFile;
    static std::mutex logMutex;
    static std::queue<std::string> logQueue;

    static unsigned maxFileSizeMB;
    static void checkMove();
    static void logHelper();

public:
    static void init(std::string logFileName, unsigned maxFileSizeMB, bool clearPrevious = false);
    static void log(LogLevel level, std::string message);
};

#endif