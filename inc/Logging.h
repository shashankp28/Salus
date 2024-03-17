#ifndef LOGGING_H
#define LOGGING_H

#include <Constants.h>
#include <fstream>
#include <string>
#include <mutex>


class Logging
{

private:
    static std::string logFilePath;
    static std::ofstream logFile;
    static std::mutex logMutex;
    static unsigned maxFileSizeMB;
    static void checkMove();
    static void logHelper(LogLevel level, std::string message);

public:
    static void init(std::string logFileName, unsigned maxFileSizeMB, bool clearPrevious = false);
    static void log(LogLevel level, std::string message);
};

#endif