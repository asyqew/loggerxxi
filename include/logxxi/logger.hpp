#pragma once

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

namespace logxxi {

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

   public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    ~Logger() = default;

    void setLevel(LogLevel level) { current_level_ = level; }
    LogLevel getLevel() { return current_level_; }

    void log(LogLevel level, const std::string& message) {
        if (level < current_level_)
            return;

        std::string timestamp = getTimestamp();
        std::string level_str = levelToString(level);
        std::string log_entry = "[" + timestamp + "] " + level_str + " " + message;

        if (level == LogLevel::ERROR)
            std::cerr << log_entry;
        else
            std::cout << log_entry;
    }

    void debug(const std::string& message) { log(LogLevel::DEBUG, message); }
    void info(const std::string& message) { log(LogLevel::INFO, message); }
    void warning(const std::string& message) { log(LogLevel::WARNING, message); }
    void error(const std::string& message) { log(LogLevel::ERROR, message); }
};

class LogStream {
   private:
    LogLevel level_;
    std::ostringstream stream_;
    bool enabled_;

   public:
    explicit LogStream(LogLevel level) : level_(level), enabled_(level >= Logger::getInstance().getLevel()) {}

    LogStream(const LogStream&) = delete;
    LogStream& operator=(const LogStream&) = delete;

    LogStream(LogStream&&) noexcept = default;
    LogStream& operator=(LogStream&&) noexcept = default;

    ~LogStream() {
        if (enabled_) {
            Logger::getInstance().log(level_, stream_.str());
        }
    }

    template <typename T>
    LogStream& operator<<(const T& value) {
        if (enabled_)
            stream_ << value;
        return *this;
    }

    using StreamManipulator = std::ostream& (*)(std::ostream&);
    LogStream& operator<<(StreamManipulator manip) {
        if (enabled_)
            manip(stream_);
        return *this;
    }
};

class LevelProxy {
   private:
    LogLevel level_;

   public:
    explicit LevelProxy(LogLevel level) : level_(level) {}

    template <typename T>
    LogStream operator<<(const T& value) const {
        LogStream stream(level_);
        stream << value;
        return stream;
    }

    using StreamManipulator = std::ostream& (*)(std::ostream&);
    LogStream operator<<(StreamManipulator manip) const {
        LogStream stream(level_);
        stream << manip;
        return stream;
    }
};

struct LogFacade {
    const LevelProxy debug{LogLevel::DEBUG};
    const LevelProxy info{LogLevel::INFO};
    const LevelProxy warning{LogLevel::WARNING};
    const LevelProxy error{LogLevel::ERROR};
};

inline LogFacade log;

#define LOG_DEBUG(msg)                                                             \
    if (logxxi::Logger::getInstance().getLevel() <= logxxi::LogLevel::DEBUG) \
    logxxi::Logger::getInstance().debug(msg)

#define LOG_INFO(msg)                                                             \
    if (logxxi::Logger::getInstance().getLevel() <= logxxi::LogLevel::INFO) \
    logxxi::Logger::getInstance().info(msg)

#define LOG_WARNING(msg)                                                             \
    if (logxxi::Logger::getInstance().getLevel() <= logxxi::LogLevel::WARNING) \
    logxxi::Logger::getInstance().warning(msg)

#define LOG_ERROR(msg)                                                             \
    if (logxxi::Logger::getInstance().getLevel() <= logxxi::LogLevel::ERROR) \
    logxxi::Logger::getInstance().error(msg)

}  // namespace logxxi