#pragma once  // Copyright 2025 wiserin
#include <string>
#include <utility>


using str = std::string;


namespace logging {


struct ColoredBadges {
    inline static const char* red     = "\033[31m";
    inline static const char* green   = "\033[32m";
    inline static const char* yellow  = "\033[33m";
    inline static const char* blue    = "\033[34m";
    inline static const char* reset   = "\033[0m";

    inline static const std::string kDebug     = std::string(blue)    + "[DEBUG]    " + reset;
    inline static const std::string kInfo      = std::string(green)   + "[INFO]     " + reset;
    inline static const std::string kWarning   = std::string(yellow)  + "[WARNING]  " + reset;
    inline static const std::string kException = std::string(red)     + "[EXCEPTION]" + reset;
    inline static const std::string kError     = std::string(red)     + "[ERROR]    " + reset;
    inline static const std::string kCritical  = std::string(red)     + "[CRITICAL] " + reset;
};


struct Badges {
    inline static const std::string kDebug     = "[DEBUG]    ";
    inline static const std::string kInfo      = "[INFO]     ";
    inline static const std::string kWarning   = "[WARNING]  ";
    inline static const std::string kException = "[EXCEPTION]";
    inline static const std::string kError     = "[ERROR]    ";
    inline static const std::string kCritical  = "[CRITICAL] ";
};


enum class LoggerMode {
    kDebug = 0,
    kInfo,
    kWarning,
    kException,
    kError,
    kCritical
};


enum class Priority {
    kMax = 0,
    kHigh,
    kNormal,
    kLow
};


enum class LoggerIOMode {
    kAsync = 0,
    kSync
};


struct Log {
    Priority priority;
    str log;

    Log(str&& log_text, Priority priority)
            : log(std::move(log_text))
            , priority(priority) {}

    Log(Log&& log) = default;
    Log& operator=(Log&& log) = default;
};

}  // namespace logging
