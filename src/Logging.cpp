#include <Logging.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <thread>

namespace fs = std::filesystem;

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
    ss << std::put_time(&nowTm, "%Y-%m-%d|%H:%M:%S");
    return ss.str();
}

void Logging::checkMove()
{
    unsigned convertRatio = 1024 * 1024;
    if (logFile.tellp() / convertRatio > maxFileSize)
    {
        logFile.close();
        fs::path destinationPath = logFilePath + "_" + getTimeString() + ".old";
        try
        {
            fs::rename(logFilePath, destinationPath);
            logFile = std::ofstream(logFilePath, std::ios::trunc);
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << e.what() << '\n';
        }
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
