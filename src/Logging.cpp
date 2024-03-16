#include <mutex>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <cstdio>
#include <Logging.h>

void Logging::init(std::string logFileName, unsigned maxFileSize, bool clearPrevious = false)
{
    logFilePath = "./log/" + logFileName;
    logFile = std::ofstream(logFileName, clearPrevious ? std::ios::trunc : std::ios::app);
    maxFileSize = maxFileSize;
}

std::string Logging::getTimeString()
{
    auto now = std::chrono::system_clock::now();
    auto nowAsTimeT = std::chrono::system_clock::to_time_t(now);
    std::tm nowTm = *std::localtime(&nowAsTimeT);
    std::stringstream ss;
    ss << std::put_time(&nowTm, "%Y-%m-%d_%H-%M-%S");
    return ss.str();
}

void Logging::checkMove()
{
    logFile.seekp(0, std::ios::end);
    long fileSize = logFile.tellp();
    logFile.seekp(0, std::ios::beg);
    unsigned convertRatio = 1024 * 1024;
    if (fileSize / convertRatio > maxFileSize)
    {
        logFile.close();
        std::string destinationPath = logFilePath + "_" + getTimeString() + ".old";
        if (std::rename(logFilePath.c_str(), destinationPath.c_str()) != 0)
        {
            std::perror("Error renaming log file");
            return;
        }
        logFile.open(logFilePath, std::ios::out | std::ios::trunc);
    }
}

std::string Logging::getLevelString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::DEBUG:
        return "DEBUG";
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARN:
        return "WARN";
    case LogLevel::ERROR:
        return "ERROR";
    case LogLevel::FATAL:
        return "FATAL";
    default:
        return "UNKNOWN";
    }
}

void Logging::logHelper(std::string message, LogLevel level = LogLevel::INFO)
{
    logMutex.lock();
    std::string fullMessage = "";
    fullMessage += "[ " + getTimeString() + " ] ";
    fullMessage += "[ " + getLevelString(level) + " ]: ";
    fullMessage += message;
    logFile << message << std::endl;
    logFile.flush();
    checkMove();
    logMutex.unlock();
}

void Logging::log(std::string message, LogLevel level = LogLevel::INFO)
{
    std::thread logThread(&Logging::logHelper, std::move(message), level);
    logThread.detach();
}
