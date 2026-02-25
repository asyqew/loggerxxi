#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

namespace loggerxxi {

enum class LogLevel { DEBUG = 0, INFO = 1, WARNING = 2, ERROR = 3 };

class Logger {
   private:
    LogLevel current_level_;

    Logger(LogLevel level = LogLevel::INFO) : current_level_(level) {}

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    std::string getTimestamp() {
        auto now = std::time(nullptr);
        auto* timeinfo = std::localtime(&now);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", timeinfo);
        return std::string(buffer);
    }
    std::string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG:
                return "\033[34m[DBG]\033[0m";
            case LogLevel::INFO:
                return "[INF]";
            case LogLevel::WARNING:
                return "\033[33m[WRN]\033[0m";
            case LogLevel::ERROR:
                return "\033[31m[ERR]\033[0m";
            default:
                return "[UKN]";
        }
    }
    void log(LogLevel level, const std::string& message) {
        if (level < current_level_)
            return;

        std::string timestamp = getTimestamp();
        std::string level_str = levelToString(level);
        std::string log_entry = "[" + timestamp + "] " + level_str + " " + message + "\n";

        if (current_level_ == LogLevel::ERROR)
            std::cerr << log_entry;
        else
            std::cout << log_entry;
    }

   public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    ~Logger() = default;

    void setLevel(LogLevel level) { current_level_ = level; }
    LogLevel getLevel() { return current_level_; }

    void debug(const std::string& message) { log(LogLevel::DEBUG, message); }
    void info(const std::string& message) { log(LogLevel::INFO, message); }
    void warning(const std::string& message) { log(LogLevel::WARNING, message); }
    void error(const std::string& message) { log(LogLevel::ERROR, message); }
};

#define LOG_DEBUG(msg)                                                             \
    if (loggerxxi::Logger::getInstance().getLevel() <= loggerxxi::LogLevel::DEBUG) \
    loggerxxi::Logger::getInstance().debug(msg)

#define LOG_INFO(msg)                                                             \
    if (loggerxxi::Logger::getInstance().getLevel() <= loggerxxi::LogLevel::INFO) \
    loggerxxi::Logger::getInstance().info(msg)

#define LOG_WARNING(msg)                                                             \
    if (loggerxxi::Logger::getInstance().getLevel() <= loggerxxi::LogLevel::WARNING) \
    loggerxxi::Logger::getInstance().warning(msg)

#define LOG_ERROR(msg)                                                             \
    if (loggerxxi::Logger::getInstance().getLevel() <= loggerxxi::LogLevel::ERROR) \
    loggerxxi::Logger::getInstance().error(msg)

}  // namespace loggerxxi