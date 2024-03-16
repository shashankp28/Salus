#ifndef LOGGING_H
#define LOGGING_H

#include <Constants.h>
#include <fstream>
#include <mutex>

class Logging
{

private:
    static std::ofstream logFile;
    static std::mutex logMutex;
};

#endif