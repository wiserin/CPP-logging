#pragma once  // Copyright 2025 wiserin
#include <string>
#include <utility>


namespace logging {

enum class LoggerMode {
    kDebug = 0,
    kTesting,
    kProduction
};


enum class Proirity {
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
    Proirity priority;
    std::string log;

    Log(std::string&& log_text, Proirity priority)
            : log(std::move(log_text))
            , priority(priority) {}

    Log(Log&& log) = default;
    Log& operator=(Log&& log) = default;
};

}  // namespace logging
