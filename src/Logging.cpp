#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <iomanip>
#include <mutex>
#include <chrono>
#include <sstream>
#include <thread>
#include <cstdio>
#include <Logging.h>

bool directoryExists(const std::string &path)
{
    struct stat info;
    return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
}

std::string getTimeString()
{
    auto now = std::chrono::system_clock::now();
    auto nowAsTimeT = std::chrono::system_clock::to_time_t(now);
    std::tm nowTm = *std::localtime(&nowAsTimeT);
    std::stringstream ss;
    ss << std::put_time(&nowTm, "%Y-%m-%d_%H-%M-%S");
    return ss.str();
}

std::string getLevelString(LogLevel level)
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

void Logging::init(std::string logFileName, unsigned maxFileSize, bool clearPrevious)
{
    if (!directoryExists("./log"))
    {
        if (mkdir("./log", 0777) != 0)
        {
            throw std::runtime_error("Failed to create log directory!");
        }
    }
    logFilePath = "./log/" + logFileName;
    logFile = std::ofstream(logFileName, clearPrevious ? std::ios::trunc : std::ios::app);
    if (!logFile.is_open())
    {
        throw std::runtime_error("Failed to open log file: " + logFilePath);
    }
    maxFileSize = maxFileSize;
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

void Logging::logHelper(std::string message, LogLevel level)
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

void Logging::log(std::string message, LogLevel level)
{
    std::thread logThread(&Logging::logHelper, std::move(message), level);
    logThread.detach();
}
