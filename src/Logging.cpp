#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <iomanip>
#include <mutex>
#include <chrono>
#include <queue>
#include <sstream>
#include <thread>
#include <cstdio>
#include <Logging.h>

std::string Logging::logFilePath;
std::ofstream Logging::logFile;
std::mutex Logging::logMutex;
std::queue<std::string> Logging::logQueue;
unsigned Logging::maxFileSizeMB;

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
    ss << std::put_time(&nowTm, "%d/%m/%Y-%H:%M:%S");
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

void Logging::init(std::string logFileName, unsigned maxFileSizeMB, bool clearPrevious)
{
    logQueue = std::queue<std::string>();
    if (!directoryExists("./log"))
    {
        if (mkdir("./log", 0777) != 0)
        {
            throw std::runtime_error("Failed to create log directory!");
        }
    }
    logFilePath = "./log/" + logFileName;
    logFile = std::ofstream(logFilePath, clearPrevious ? std::ios::trunc : std::ios::app);
    if (!logFile.is_open())
    {
        throw std::runtime_error("Failed to open log file: " + logFilePath);
    }
    logFile.close();
    maxFileSizeMB = maxFileSizeMB;
    std::thread logThread(&Logging::logHelper);
    logThread.detach();
}

void Logging::checkMove()
{
    logFile.seekp(0, std::ios::end);
    long fileSize = logFile.tellp();
    logFile.seekp(0, std::ios::beg);
    unsigned convertRatio = 1024 * 1024;
    if (fileSize / convertRatio > maxFileSizeMB)
    {
        std::string destinationPath = logFilePath + "_" + getTimeString() + ".old";
        if (std::rename(logFilePath.c_str(), destinationPath.c_str()) != 0)
        {
            std::perror("Error renaming log file");
            return;
        }
        logFile = std::ofstream(logFilePath, std::ios::trunc);
        if (!logFile.is_open())
        {
            throw std::runtime_error("Failed to create new log file: " + logFilePath);
        }
        logFile.close();
    }
}

void Logging::logHelper()
{
    while (true)
    {
        while (!logQueue.empty())
        {
            logMutex.lock();
            logFile.open(logFilePath, std::ios::app);
            std::string message = logQueue.front();
            logQueue.pop();
            logFile << message << std::endl;
            logFile.flush();
            logFile.close();
            checkMove();
            logMutex.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Logging::log(LogLevel level, std::string message)
{
    std::string fullMessage = "";
    fullMessage += "[ " + getTimeString() + " ] ";
    fullMessage += "[ " + getLevelString(level) + " ]: ";
    fullMessage += message;
    logQueue.push(fullMessage);
}
